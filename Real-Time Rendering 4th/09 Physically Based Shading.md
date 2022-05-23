# Chapter 9 基于物理的着色（Physically Based Shading）

## 9.10 布料的BRDF模型（BRDF Models for Cloth）

布料往往具有不同于其他类型材料的微观几何形状。 根据织物类型，它可能具有高度重复的编织微结构、从表面垂直突出的圆柱体（cylinders）（线（threads）），或两者兼而有之。 因此，布料表面具有与众不同的表现，通常需要专门的着色模型，例如各向异性镜面高光（anisotropic specular highlights）、粗糙散射（asperity scattering） ^[919]^（光通过突出的半透明纤维散射引起的明亮边缘效应），甚至颜色随观察方向的变化（ 由穿过织物的不同颜色的线引起）。

除了 BRDF，大多数织物都具有高频空间变化，这也是创造令人信服的布料外观的关键 ^[825]^。 请参见图 9.42。

![Figure 9.42](E:\My Documents\Github\MyImageBed\Real-Time Rendering 4th\Chapter 09\Figure 9.42.png "图 9.42")

**图 9.42 使用为游戏 Uncharted 4 构建的布料系统的材质。**

左上方的球体具有标准 BRDF，具有 GGX 微平面镜面反射和 Lambertian 漫反射。 上部中间球体使用了织物BRDF。 其他每个球体都添加了不同类型的逐像素变化，从左到右、从上到下分别为：织物编织细节（fabric weave details）、织物老化（fabric aging）、瑕疵细节（imperfection details）和小褶皱（small wrinkles）。 （《神秘海域4：盗贼末路》（UNCHARTED 4 A Thief's End）由顽皮狗公司（Naughty Dog LLC） 创建和开发。）

------

布料 BRDF 模型分为三大类：通过观察创建的经验模型、基于微平面理论的模型和微圆柱模型。 我们将回顾每个类别的一些值得注意的例子。

### 9.10.1 经验布料模型（Empirical Cloth Models）

在游戏 《神秘海域 2》（Uncharted 2） ^[631]^ 中，布料表面使用以下漫反射 BRDF 形式：
$$
f_{diff}(\mathbf{l},\mathbf{v})=\frac{\rho_{ss}}{\pi}(k_{rim}((\mathbf{v}\cdot \mathbf{n})^+)^{\alpha_{rim}}+k_{inner}(1-(\mathbf{v}\cdot \mathbf{n})^+)^{\alpha_{inner}}+k_{diff}),\tag{9.70}
$$
其中 $k_{rim},k_{inner},$ 和 $k_{diff}$ 分别是用户控制的 边缘光（rim lighting）项、照亮前部（inner）表面（brighten forward-facing）的项和 Lambertian 项的缩放因子。 此外，$α_{rim}$ 和 $α_{inner}$ 控制 rim 项和 inner 项的衰减。 这种行为是非物理的，因为有几个依赖于视角（view-dependent）的效果，但没有一个依赖于光源方向的效果。

相比之下，《神秘海域4》（Uncharted 4） ^[825]^ 中的布料对于镜面反射项使用微平面或微圆柱模型，具体取决于布料类型（如以下两节所述），对于漫反射项使用“环绕照明（wrap lighting）”的经验次表面散射近似：
$$
f_{diff}(\mathbf{l},\mathbf{v})(\mathbf{n},\mathbf{l})^+\Rightarrow\frac{\rho_{ss}}{\pi}(c_{scatter}+(\mathbf{n},\mathbf{l})^+)^{\mp}\frac{(\mathbf{n},\mathbf{l}+\omega)^\mp}{1+\omega}.\tag{9.71}
$$
这里我们使用 1.2 节介绍的 $(x)^\mp$ 符号，它表示 0 和 1 之间的钳制。怪异的符号 $f_{diff}(\mathbf{l},\mathbf{v})(\mathbf{n},\mathbf{l})^+\Rightarrow...$ 表示此模型会影响照明以及 BRDF。 箭头右侧的项取代了左侧的项。 用户指定的参数 $c_{scatter}$ 表示散射颜色，参数 $\omega$，范围为 $[0, 1]$，控制环绕照明宽度。

对于布料建模，Disney 使用他们的漫反射 BRDF 项 ^[214]^（第 9.9.4 节），并在模型的粗糙散射中添加了一个光泽（sheen）项：
$$
f_{sheen}(\mathbf{l},\mathbf{v})=k_{sheen}c_{sheen}(1-(\mathbf{h},\mathbf{l})^+)^5,\tag{9.72}
$$
其中 $k_{sheen}$ 是调节光泽项强度的用户参数。 光泽颜色 $c_{sheen}$ 是白色和 $\rho_{ss}$ 的亮度归一化（luminance-normalized）值之间的混合（由另一个用户参数控制）。 换句话说，$ρ_{ss}$ 除以其亮度（luminance）来隔离其色调（hue）和饱和度（saturation）。

### 9.10.2 微平面布料模型（Microfacet Cloth Models）









## 符号和定义

* $x^+$：将 $x$ 钳制为 $0$（非负）
* $x^\mp$：将 $x$ 钳制到 $0\leq x\leq 1$



## 参考文献

* [214] Burley, Brent, “Physically Based Shading at Disney,” SIGGRAPH Practical Physically Based Shading in Film and Game Production course, Aug. 2012. Cited on p. 325, 336, 340, 342, 345, 353, 354, 357, 364
* [631] Hable, John, “Uncharted 2: Character Lighting and Shading,” SIGGRAPH Advances in Real-Time Rendering in Games course, July 2010. Cited on p. 357, 635
* [825] Jiang, Yibing, “The Process of Creating Volumetric-Based Materials in Uncharted 4,” SIGGRAPH Advances in Real-Time Rendering in Games course, July 2016. Cited on p. 356, 357, 358, 359
* [919] Koenderink, Jan J., and Sylvia Pont, “The Secret of Velvety Skin,” Journal of Machine Vision and Applications, vol. 14, no. 4, pp. 260–268, 2002. Cited on p. 356