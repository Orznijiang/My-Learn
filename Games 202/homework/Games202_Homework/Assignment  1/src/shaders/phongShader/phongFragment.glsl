#ifdef GL_ES
precision mediump float;
#endif

// Phong related variables
uniform sampler2D uSampler;
uniform vec3 uKd;
uniform vec3 uKs;
uniform vec3 uLightPos;
uniform vec3 uCameraPos;
uniform vec3 uLightIntensity;

varying highp vec2 vTextureCoord;
varying highp vec3 vFragPos;
varying highp vec3 vNormal;

// Shadow map related variables
#define NUM_SAMPLES 100
#define BLOCKER_SEARCH_NUM_SAMPLES NUM_SAMPLES
#define PCF_NUM_SAMPLES NUM_SAMPLES
#define NUM_RINGS 10

#define EPS 1e-4
#define PI 3.141592653589793
#define PI2 6.283185307179586

#define LIGHT_WIDTH 20.0
#define CAMERA_WIDTH 360.0
#define SHADOWMAP_RESOLUSION 2048.0
#define BASE_BIAS 0.00001
#define MAX_ADAPTIVE_BIAS 0.005
#define BIAS_SCALE 0.5

#define C_DEPTH 1.0
#define C_NORMAL 1.0

uniform sampler2D uShadowMap;

varying vec4 vPositionFromLight;

highp float rand_1to1(highp float x ) { 
  // -1 -1
  return fract(sin(x)*10000.0);
}

highp float rand_2to1(vec2 uv ) { 
  // 0 - 1
	const highp float a = 12.9898, b = 78.233, c = 43758.5453;
	highp float dt = dot( uv.xy, vec2( a,b ) ), sn = mod( dt, PI );
	return fract(sin(sn) * c);
}

float unpack(vec4 rgbaDepth) {
    const vec4 bitShift = vec4(1.0, 1.0/256.0, 1.0/(256.0*256.0), 1.0/(256.0*256.0*256.0));
    return dot(rgbaDepth, bitShift);
}

vec2 poissonDisk[NUM_SAMPLES];

void poissonDiskSamples( const in vec2 randomSeed ) {

  float ANGLE_STEP = PI2 * float( NUM_RINGS ) / float( NUM_SAMPLES );
  float INV_NUM_SAMPLES = 1.0 / float( NUM_SAMPLES );

  float angle = rand_2to1( randomSeed ) * PI2;
  float radius = INV_NUM_SAMPLES;
  float radiusStep = radius;

  for( int i = 0; i < NUM_SAMPLES; i ++ ) {
    poissonDisk[i] = vec2( cos( angle ), sin( angle ) ) * pow( radius, 0.75 );
    radius += radiusStep;
    angle += ANGLE_STEP;
  }
}

void uniformDiskSamples( const in vec2 randomSeed ) {

  float randNum = rand_2to1(randomSeed);
  float sampleX = rand_1to1( randNum ) ;
  float sampleY = rand_1to1( sampleX ) ;

  float angle = sampleX * PI2;
  float radius = sqrt(sampleY);

  for( int i = 0; i < NUM_SAMPLES; i ++ ) {
    poissonDisk[i] = vec2( radius * cos(angle) , radius * sin(angle)  );

    sampleX = rand_1to1( sampleY ) ;
    sampleY = rand_1to1( sampleX ) ;

    angle = sampleX * PI2;
    radius = sqrt(sampleY);
  }
}

float calBias(){
    //vec3 lightDir = normalize(uLightPos - vFragPos);
    vec3 lightDir = normalize(uLightPos);
    vec3 normalDir = normalize(vNormal);
    float cos_LN = clamp(dot(lightDir, normalDir), 0.000001, 1.0);
    float sin_LN = sqrt(1.0 - cos_LN * cos_LN);
    float tan_LN = sin_LN / cos_LN;
    float scale = 1.0 / SHADOWMAP_RESOLUSION / 2.0;
    float adaptive_bias = clamp(scale * tan_LN, 0.0, MAX_ADAPTIVE_BIAS);
    float bias = BASE_BIAS + BIAS_SCALE * adaptive_bias;
    return bias;
}

float bias_depth(){
    vec3 lightDir = normalize(uLightPos);
    vec3 normalDir = normalize(vNormal);
    float cos_LN = clamp(dot(lightDir, normalDir), 0.000001, 1.0);
    float sin_LN = sqrt(1.0 - cos_LN * cos_LN);
    float tan_LN = sin_LN / cos_LN;
    float scale = 1.0 / SHADOWMAP_RESOLUSION / 2.0;
    float bias = scale * tan_LN * C_DEPTH;
    return bias;
}

float bias_normal(){
    vec3 lightDir = normalize(uLightPos);
    vec3 normalDir = normalize(vNormal);
    float cos_LN = clamp(dot(lightDir, normalDir), 0.000001, 1.0);
    float sin_LN = sqrt(1.0 - cos_LN * cos_LN);
    float scale = 1.0 / SHADOWMAP_RESOLUSION / 2.0;
    float bias = scale * sin_LN * C_NORMAL;
    return bias;
}

float findBlocker( sampler2D shadowMap,  vec2 uv, float zReceiver ) {
    //uniformDiskSamples(uv);
    poissonDiskSamples(uv);
    float block_num = 0.0;
    float block_depth = 0.0;
    for(int i = 0; i < BLOCKER_SEARCH_NUM_SAMPLES; i++){
      float radius = zReceiver * LIGHT_WIDTH / CAMERA_WIDTH / 2.0 * SHADOWMAP_RESOLUSION;
      vec2 uv_bias = poissonDisk[i] * radius / SHADOWMAP_RESOLUSION;
      //vec2 uv_bias = poissonDisk[i] * 2.0 / SHADOWMAP_RESOLUSION;//??????????????????blocker???receiver?????????????????????????????????????????????
      float shadowDepth = unpack(texture2D(shadowMap, uv + uv_bias));
      
      if(zReceiver > shadowDepth + (1.0 + radius) * bias_normal()){
        block_num++;
        block_depth += shadowDepth;
      }
    }
    if(block_num > 0.0){
      float avg_depth = block_depth / block_num;
      if(zReceiver > avg_depth){
        return avg_depth;
      }
    }
  	return 1.0;
}

float PCF(sampler2D shadowMap, vec4 coords, float radius) {
  //uniformDiskSamples(coords.xy);
  poissonDiskSamples(coords.xy);
  float blocker = 0.0;
  for(int i = 0; i < NUM_SAMPLES; i++){
    vec2 uv_bias = poissonDisk[i] * radius / SHADOWMAP_RESOLUSION;
    float shadowDepth = unpack(texture2D(shadowMap, coords.xy + uv_bias));
    float uv_bias_length = sqrt(uv_bias.x * uv_bias.x + uv_bias.y * uv_bias.y);
    if(coords.z > shadowDepth + (1.0 + radius) * bias_normal()){
      blocker++;
    }
  }
  return 1.0 - blocker / float(NUM_SAMPLES);
}

float PCSS(sampler2D shadowMap, vec4 coords){

  // STEP 1: avgblocker depth
  float avgBlocker = findBlocker(shadowMap, coords.xy, coords.z);
  if(avgBlocker > 0.999){
    return 1.0;
  }

  // STEP 2: penumbra size
  //float light_width = 20.0;
  float penumbra = (coords.z - avgBlocker) * LIGHT_WIDTH / avgBlocker;

  // STEP 3: filtering 
  return PCF(shadowMap, coords, penumbra + 2.0);
}


float useShadowMap(sampler2D shadowMap, vec4 shadowCoord){
  vec4 packedShadowDepth = texture2D(shadowMap, shadowCoord.xy).rgba;
  float shadowDepth = unpack(packedShadowDepth);


  if(shadowCoord.z > shadowDepth + bias_normal()){
    return 0.0;
  }
  return 1.0;
}

vec3 blinnPhong() {
  vec3 color = texture2D(uSampler, vTextureCoord).rgb;
  color = pow(color, vec3(2.2));

  vec3 ambient = 0.05 * color;

  vec3 lightDir = normalize(uLightPos);
  vec3 normal = normalize(vNormal);
  float diff = max(dot(lightDir, normal), 0.0);
  vec3 light_atten_coff =
      uLightIntensity / pow(length(uLightPos - vFragPos), 2.0);
  vec3 diffuse = diff * light_atten_coff * color;

  vec3 viewDir = normalize(uCameraPos - vFragPos);
  vec3 halfDir = normalize((lightDir + viewDir));
  float spec = pow(max(dot(halfDir, normal), 0.0), 32.0);
  vec3 specular = uKs * light_atten_coff * spec;

  vec3 radiance = (ambient + diffuse + specular);
  vec3 phongColor = pow(radiance, vec3(1.0 / 2.2));
  return phongColor;
}

void main(void) {
  vec3 shadowCoord = ((vPositionFromLight.xyz / vPositionFromLight.w) + 1.0) / 2.0;

  float visibility;
  //visibility = useShadowMap(uShadowMap, vec4(shadowCoord, 1.0));
  //visibility = PCF(uShadowMap, vec4(shadowCoord, 1.0), 5.0);
  visibility = PCSS(uShadowMap, vec4(shadowCoord, 1.0));

  vec3 phongColor = blinnPhong();
  vec3 ambient = 0.15 * pow(texture2D(uSampler, vTextureCoord).rgb, vec3(2.2));

  gl_FragColor = vec4(phongColor * visibility + ambient, 1.0);
  //gl_FragColor = vec4(phongColor * visibility, 1.0);
  //gl_FragColor = vec4(vec3(visibility), 1.0);
  //gl_FragColor = vec4(findBlocker(uShadowMap, shadowCoord.xy, shadowCoord.z));
  //gl_FragColor = vec4(phongColor, 1.0);
  //gl_FragColor = (vPositionFromLight + 1.0) / 2.0;
  //gl_FragColor = vec4(unpack(texture2D(uShadowMap, shadowCoord.xy + vec2(0.1,0.1))));
}