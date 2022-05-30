# Fitting Procedural Yarn Models for Realistic Cloth Rendering

## 摘要

织物在许多设计、原型制作和娱乐相关的应用中发挥着重要作用。近期提出的基于纤维的模型能够成功地捕捉到织物丰富的视觉外观，但是往往存在设计和编辑过于繁琐的弊端。另一方面，基于纱线的程序化模型功能强大且使用便捷，但是效果过于平常，外观不够逼真。这篇文章介绍了一种用于创建具有纤维级别细节程度的织物的高质量程序化纱线模型的自动拟合方法。我们将CT数据拟合到程序化模型中以自动化恢复所有的参数，并且使用了基于测量的飞散纤维模型来增强自己的模型。我们根据CT的实际测量值和真实照片验证了自己模型的可用性，并展示了这种方法在织物建模和编辑中的实用性。



## 关键字

* 外观建模（appearance modeling）
* 程序几何图形（procedural geometry）
* 纺织品（textile）



## 概念

计算方法论 -> 渲染

（Computing methodologies -> Rendering）



## 1 介绍

布料对我们的日常生活至关重要。对它们进行虚拟建模和设计对于许多应用程序（例如在线零售、纺织品设计）以及娱乐应用程序（例如游戏和电影）来说非常重要。尽管计算机图形学有着悠久的历史，对织物进行准确的建模仍然具有挑战性。织物在结构性和光学性上都非常复杂，导致不同织物的外观变化十分巨大。

在虚拟模型中表现织物的丰富性，积极推动了各种织物外观模型的研究。最近，基于微外观的织物模型<sup>[9] [14] [20] [21]</sup>已经介绍了如何显式捕获织物的微观几何形状。和传统的方法相比，这些模型以前所未有的细节描述织物，因此具有优越的通用性，因为织物的复杂外观很大程度上是其小规模结构的直接结果。

由于纤维级别的细节会很大程度上影响织物的整体外观，因此准确捕捉它们对于前瞻预览的应用（即得到成品前的设计应用，如纺织品设计）至关重要。以前，这些详细的结构是通过体积成像（例如计算机显微断层扫描）测量的，从而生成高分辨率的3D体积<sup>[20] [21]</sup>或大量无组织的纤维曲线<sup>[9]</sup>。这两种表示都不容易操作。另一方面，基于纱线的模型<sup>[1] [7]</sup>更适合编辑和模拟<sup>[19]</sup>，但没有捕捉到实现真实感所需的具有丰富细节的纤维级结构。参见图 1-c，其中纱线（yarn）像是由塑料制成的，因为它们错过了许多纤维级结构产生的细节高光。将便利性和易于建模的特性与复杂外观的特性结合衔接起来，对于采用细节丰富的织物模型至关重要。

![Figure 1](https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%201.png?raw=true "图 1")

**图 1：我们提出了一种新技术来自动生成纱线几何结构的程序化表示。 **

基于物理纱线样品的几何测量 (a)，我们的方法拟合了纤维几何形状的统计表示以与现实情况密切匹配 (b)。 

(a, b) 中从上到下的四种纱线是棉（cotton）、人造丝（rayon）、丝绸（silk）和涤纶（polyester）。 

我们的拟合模型可以将真实的纤维级细节填充到基于纱线的织物模型中（该模型可使用纺织品设计软件或基于物理的纱线模拟生成），以显着提高渲染织物的质量（c-top 与 c-middle（我们的成果） ）。 我们的程序化模型携带高级人为定义的信息（例如，捻度和毛发量），可提供简便的可编辑性（c-bottom）。

------



这篇文章介绍了一种自动化建模过程，该过程进行物理 CT 测量（图 1-a）并计算织物纱线的程序化描述（图1-b）。 其输出可用于将逼真的纤维级细节填充到基于纱线的模型中（图 1-c，中间），显着提高了最终输出的真实性。 此外，这种参数化模型易于编辑，并产生与纱线在真实世界中的表现相匹配的显著的外观变化（图1-c，底部）。

织物的微观几何形状已经在纺织品相关的研究（n）中得到了广泛研究（v）。最近， Schroder等人<sup>[14]</sup>利用该领域的最新成果，将程序化的纱线模型引入了计算机图形学<sup>[8] [10] [16]</sup>。他们的模型以基于易于编辑的统计分布来表示织物纱线。然而，如何为这个模型设置参数值以紧密匹配真实的织物仍然是一个重大的挑战。在 Schroder 等人的成果中<sup>[14]</sup>，创建程序化纱线是一个手动过程。 但这种拟合是一个trick。 如图 2 所示，从扭曲度到毛发量的纤维相关属性的改变会极大地影响织物的整体外观。 因此，妥当地拟合这些参数对于正确再现现实世界的织物的视觉特征至关重要。 但这很难手动完成，因为纤维级结构太小以致无法观察，并且适当地设置相应的参数需要对 3D 微观几何形状进行仔细分析，而这些几何形状在没有体积测量的情况下很难获得。

![Figure 2](https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%202.png?raw=true "图 2")

图 2：具有相同的纱线级别几何形状但是纤维级别属性不同的渲染织物：

* （a）原始
* （b）修改纤维扭曲度（twisting）
* （c）修改纤维分布
* （d）增加飞线（flyaway）变动

这些纤维级别的变化会在更大的尺度上改变外观表现。

------

在这篇文章中，我们提出了一项新技术，可以根据现实中纱线的物理测量值自动创建程序化纱线模型。 其贡献包括：

* 一个端到端的管线，用于从使用微型 CT 成像 (§4) 获得的物理测量值中自动构建其模型
* 一种改进的飞线纤维模型，不仅在统计学上更有意义，而且更容易拟合（§5）
* 通过与 CT 测量值和照片（§6）进行比较来验证其拟合结果

我们正在发布这些技术的实现、测量数据和拟合参数（表 2）。 他们的开发的工具和数据允许将纤维级细节添加到基于纱线的布料设计中，这种布料设计在纺织品软件<sup>[12]</sup>和模拟工具<sup>[1] [7]</sup>中被使用。 添加的细节可以显着提高渲染质量（图 1 和 图 17），对设计应用程序来说作用巨大。



## 2 相关工作

### 织物外观（Fabric appearance）

几十年来，织物外观一直是计算机图形学中的一个活跃研究课题。 传统上，将织物看作无限薄的二维面。 许多表面反射模型已经被提出用来模拟织物外观<sup>[4] [13]</sup>。 尽管这些模型为从远处观看的织物提供了高质量的渲染，但它们缺乏精确再现粗纱或有毛绒感的织物外观的能力，也缺乏处理外观差异很大的不同织物的通用性。

![Figure 3](https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%203.png?raw=true "图 3")

图 3：织物结构：一根纱线（yarn）通常由多个称为股（ply）的子股（sub-stands）组成。 每股（ply）依次包含数十到数百微米直径的纤维（fiber）。

------

布料外观建模的最新进展为基于体积的<sup>[5] [18] [20] [21] [22]</sup>和基于纤维的<sup>[9] [14]</sup>布料模型的发展。与传统方法不同，它们以具有不同密度（基于体积）的3D体积或纤维曲线的集合（基于纤维）来描述织物。与传统的基于表面的方法相比，这些模型更擅长捕捉织物的厚度和毛绒感，这大大增加了它们的视觉真实感，从而将计算渲染的布料质量提升到了一个新的水平。然而，这些技术要么提供高度逼真的模型的自动化创建（通过测量真实世界的样本数据来实现），但携带很少的高水平人为定义的信息（例如，纱线捻度（扭曲度））<sup>[9] [20]</sup>，或提供严谨的程序化表示，但依赖于手动配置的模型，这些模型需要进行关键的参数调整以紧密匹配现实情况<sup>[14]</sup>。我们引入了一种技术，它可以利用这两种方法的优点，同时避免它们的弱点。

### 织物几何形状（Fabric geometry）

数十年来，纺织品研究界一直在研究织物的几何结构。 根据该领域的最新成果<sup>[8] [10] [15] [16]</sup>发展出了一些上述的微观外观建模技术<sup>[14] [20]</sup>。

### 基于纱线的面料（Yarn-based fabrics）

基于纱线的表示方法在纱线级别（相对于纤维级别）对织物进行描述，几乎专门用于纺织品设计<sup>[12]</sup>。 最近，基于纱线的模拟<sup>[1] [7]</sup>和编辑<sup>[19]</sup>已在计算机图形学得到发展。 然而，这些模型的渲染质量通常很有限，因为它们缺乏对织物整体外观有很大影响的纤维级别细节。我们的方法生成的程序化模型能够弥补这个差距：它们可用于在纱线模型中加入纤维级别的结构细节，从而显着提高其外观的虚拟真实感。



## 3 背景

该部分讨论了织物微观外观建模技术（§3.1）和程序纱线模型（§3.2）的先前工作。



------

**算法 1** 程序化纱线生成（procedural yarn generation）

------

​	1：**for** each ply $i$ **do**

​	2：       generate regular fibers using 公式（1）（2）（3）

​	3：	   add flyaway fibers

​	4：	   scale all fibers in the ply to obtain elliptical cross-section

​	5：**end for**

​	6：twist all plies together around the yarn center

------



------

**算法 2** 横截面纤维位置采样（Sampling cross-sectional fiber location）

------

**Require**：cross-section fiber distribution parameters $\epsilon,\beta$

​	1：**procedure** SAMPLEFIBERLOCATION$(\epsilon,\beta)$

​	2：	   **repeat**

​	3：	   	   draw $(x,y)$ uniformly in a unit disc

​	4：			  draw $\xi$ form $U[0,1]$

​	5：	   **until** $\xi<p(||(x,y)||_2)$ （ $p$ defined in 公式（1））

​	6：	   **return** $(x,y)$

​	7：**end procedure**

------

### 3.1 织物微外观建模（Fabric Micro-Appearance Modeling）

织物是通过编织和针织等制造技术来结合多种纱线而制成的，而其中每根纱线都是通过加捻（如果纺丝的一端被握持住，另一端回转，即可形成纱线，这一过程称为加捻）数百个微米直径的纤维制成的。 现实世界的纱线通常由多股子股（ sub-strands）或股线（plies）组成（图 3）。 最近，基于纤维的模型通过显式表示纱线和股线的真实结构来实现其视觉准确性。 这些模型可以分为两大类：基于体积的和基于纤维的。

#### 体积模型（Volumetric models）

体积模型使用通过处理微型 CT 测量获得的高分辨率 3D 体积来描述织物的微观几何形状<sup>[20]</sup>。 体积中的每个点都会存储局部纤维密度和纤维方向信息。

#### 基于纤维的模型（Fiber-based models）

基于纤维的模型将织物视为被描述为一维曲线的单个纤维的集合<sup>[9] [14]</sup> 。然后将这些纤维曲线与双向曲线散射分布函数 (BCSDF) 相结合以生成渲染图像。

与体积模型相比，基于纤维的模型在更严谨并提供更多人为定义的信息的同时得到了与其在相似水平的真实感<sup>[9]</sup>。 因此，这篇文章选择在程序上生成基于纤维的表示。



### 3.2 纱线几何形状的程序化建模（Procedural Modeling of Yarn Geometry）

这篇文章建立在Schroder 等人<sup>[14]</sup>提出的基于纺织品研究的最新成果<sup>[8] [10] [16]</sup>的程序化纱线模型之上。该模型在统计上描述了单根纱线是如何由底层纤维形成的。 关键参数是：

* 对于纤维（fiber）来说：横截面上的纤维分布、纤维加捻（twisting）和纤维偏移（migration）。
* 对于股（ply）来说：股横截面、股捻度（twisting）和纤维数。

此外，该模型有一个单独的步骤，我们在 §5 中对其进行了改进，用于处理对于真实感来说非常重要的飞散纤维的效果。 在Schroder 等人的研究<sup>[14]</sup>中可了解更多详情。

#### 横截面上的纤维分布（Cross-sectional fiber distribution）

程序化纱线模型的一个关键组成部分是横截面上的纤维分布情况，通过给定其与股（ply）的中心的距离 R ∈ [0, 1) ，它可以捕捉到该位置上纤维存在的几率 。 此分布使用以下（非标准化）密度函数：
$$
p(R)=(1 - 2\epsilon)(\frac{e-e^R}{e-1})^\beta+\epsilon  \tag{1},
$$
它与拒绝采样（算法 2）一起使用以绘制横截面纤维的位置。 给定第 $i$ 个纤维的采样位置$(x_i,y_i)$ ，假设股的中心为 Z 轴，纤维曲线（作为由 $\theta$ 参数化的圆形螺旋线）可以按下面的方式生成：
$$
x(\theta)=R_icos(\theta+\theta_i),\quad y(\theta)=R_isin(\theta+\theta),\quad
z(\theta)=\frac{\alpha\theta}{2\pi}, \tag{2}
$$

其中 $R_i := ||(x_i, y_i)||^2, \theta_i := atan2(y_i, x_i),$  $α$ 是决定纤维捻度（twist）（即螺距）的常数。（atan2函数返回的是原点至点(x,y)的方位角，即与 x 轴的夹角。在数学坐标系中，结果为正表示从 X 轴逆时针旋转的角度，结果为负表示从 X 轴顺时针旋转的角度。atan2(a, b) 与atan(a/b) 稍有不同，atan2(a,b)的取值范围介于 -pi 到 pi 之间（不包括 -pi），而atan(a/b)的取值范围介于-pi/2到pi/2之间（不包括±pi/2)。若要用度表示反正切值，请将结果再乘以 180/pi。另外要注意的是，函数atan2(y,x)中参数的顺序是倒置的，atan2(y,x)计算的值相当于点(x,y)的角度值）

#### 纤维偏移（Fiber migration）

在公式 (2) 中，生成的纤维与股中心之间的距离保持不变。 但这是不自然的：纤维通常来说会偏移一段固定的距离。 这种纤维的偏移通过允许距离在两个给定的常数 $R_{min}$ 和 $R_{max}$ 之间连续变化来进行模拟。 也就是说，通过将公式 (2)中的 $R_i$ 替换为：
$$
R_i(\theta):=R_{min}R_i+\frac{(R_{max}-R_{min})R_i}{2}[cos(s\theta+\theta_i^{(0)})+1], \tag{3}
$$
其中 $s$ 是控制旋转长度的一个常数，$θ_i^{(0)}$ 是一个表示旋转的初始“相位”（phase）的逐纤维参数。

#### 股横截面（Ply cross section）

使用公式（1）和公式（3）生成的股（ply）总是具有圆形横截面。 一个简单的通用化是通过分别以 $e_X$ 和 $e_Y$ 因子沿 $X$ 和 $Y$ 方向对股（ply）进行缩放来支持椭圆横截面。

#### 飞散纤维（Flyaway fibers）

真正的纱线通常含有飞散的纤维，它们不跟随正常纤维的流动。 这些不规则性不仅极大地提高了纱线外观的真实感，而且对于再现真实织物的模糊轮廓也至关重要。 以前的工作使用 3D 柏林噪声以某种简化的方式生成飞散纤维^[14]^。 我们引入了一种改进的飞散模型（§5），该模型在统计上更有意义且更易于拟合。

#### 股捻度（Ply twisting）

构建程序纱线模型的最后一步是对每一组的股（ply）进行加捻。 对于以 Z 轴为中心的纱线，每股（ply）都被加捻以遵循圆形螺旋曲线
$$
S(z):=(S_x(z),\ S_y(z),\ z)
$$
其间距由 $α^{ply}$ 控制：
$$
S_x(z)=R^{ply}cos(2\pi z/\alpha^{ply}+\theta^{ply}),\\
S_y(z)=R^{ply}sin(2\pi z/\alpha^{ply}+\theta^{ply}),
$$
除了横截面和捻度信息外，每股都有一个与之相关的整数 m，它指定了该股由多少纤维组成。 算法 1 总结了用于程序化生成纱线几何形状的整个流程。

#### 参数拟合的挑战（Challenges in parameter fitting）

尽管通过给定模型参数，纤维生成过程（算法 1）是直接的，但翻过来对其参数进行拟合并不是一个小问题。 许多纤维级别的参数，例如横截面的纤维分布和纤维偏移，都是基于纱线微观几何形状的统计属性。 这些属性由于其微观性而难以获得，并且由于其与生俱来的不规则性而难以拟合。

在本文中我们通过使用微型 CT 成像获取纱线的微观几何形状来解决这些问题，并引入端到端的管线以自动且稳定地将程序化表示拟合到测量数据 (§4)。 此外，我们引入了一种用于模拟飞散纤维的新模型（§5），这对照片级真实感的实现大有裨益。



## 4 模型拟合（Model Fitting）

我们展示了自己的端到端管线，用于将程序化纱线拟合到微观几何形状的物理测量数据中。 需要拟合的参数总结在表 1 中。其中的挑战是将没有人为定义的信息的体积 CT 数据转换为具有正确股（ply）级别和纤维（fiber）级别属性的程序化纱线模型。 许多参数必须被合理识别以匹配物理纱线的外观。 最终，这种方法产生了一个严谨且可编辑的表示，捕捉了现实世界纱线的丰富的不规则性。

从较高的层次来看，我们的管线类似于以相反的顺序执行算法 1（图 4）。 特别是，给定测量的纱线微观几何形状（§4.1）：

* 首先，我们估计股捻度（ ply twisting）以及的组件股的横截面形状（§4.2）。 使用此信息，我们“解开”相互缠绕的组件股并对其进行形变，使它们以 Z 轴为中心并具有圆形横截面。
* 然后，我们分析每个解开的股（ply）并将组成纤维（fiber）分为两类：飞散纤维和常规纤维（第 4.3 节）。
* 接下来，根据获得的飞散纤维，确定我们改进的模型所需的参数值（§5.2）。
* 最后，我们使用先前获得的常规纤维（§4.4）拟合横截面纤维分布和偏移参数。

在本节的其余部分，我们首先描述他们利用最先进技术的 CT 成像过程阶段^[9][21]^为我们的主要拟合管线（§4.1）获得简洁的输入几何数据。 然后，我们按照算法 1 的流程解释我们的管线（即 图 4 中从右到左）。

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%204.png?raw=true" title="图 4" style="zoom:50%;" />

图 4：**我们引入的参数拟合管线。** 该管线与程序化纱线生成算法（算法 1）的顺序大致相反，因为它对参数进行拟合。

------

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Table%201.png?raw=true" title="表 1" style="zoom: 67%;" />

表 1：程序化纱线模型使用的**参数列表**。 紫色显示的参数是相对于股（ply）的属性。 以蓝色显示的那些参数是为每根纤维通过独立采样相应的统计分布来指定的。 特别是，逐纤维的飞散参数（即 $R^{loop}_{max},\ R^{hair}_{min},\ R^{hair}_{span}\ and\ θ^{hair}_{span}$）是从正态分布中采样的（参见 §5 和表 2），而其他参数（即 $R_i,\ θ_i\ and\ θ^{(0)}_i$ ) 被均匀绘制（§3.2）。

------

### 4.1 输入（Input）

我们使用显微 CT 成像获取物理纱线的微观几何形状。 如图 5-a 所示，由于可以同时扫描多根纱线，因此可以将多根纱线打包在一起以加快采集速度。 给定具有体积纤维密度的微观 CT 测量值（图 5-b），使用 Khungurn 等人开发的方法^[9]^对其进行处理来提取纤维曲线（图 5-c）。 此外，我们对纱线进行跟踪^[21]^来提取每个组件股的中心曲线（图5-d）。恢复的纤维曲线和股中心（图 5-cd）作为其主要参数拟合管线的输入。

### 4.2 股捻度和横截面估计（Ply Twisting and Cross Section Estimation）

我们的参数拟合管线的第一步是复原输入纱线的合股（plying）（即股捻度和横截面形状），以便我们可以分离出单个股并执行后面的逐股分析。 在本文中，我们假设纱线中的所有股线都是相同的，并且均匀分布在纱线中心周围。

#### 股捻度（Ply twisting）

对于每个给定的股（ply）中心 $i$（表示为多段线（poly-line）），我们以公式（4）的形式拟合螺旋曲线 $S_i$。这需要估计股半径 $R^{ply}_i$ ，螺距 $α^{ply}_i$ 和初始角度 $θ^{ply}_i$。鉴于我们假设股线相同且分布均匀，这归结为发现：

* 所有股公用的一组 $R_{ply}$ 和 $α_{ply}$；
* $θ^{ply}_1$ ，即第一条股的初始角度，这个值可以通过设置 $θ_i^{ply}=θ^{ply}_1+2π\frac{i-1}{K}$ 来确定所有其他股的初始角度。

为了确定这些参数，我们通过最小化来优化给定的和拟合的股中心之间的 L2 距离：
$$
\quad E^{ply}(R^{ply},\alpha^{ply},\theta_1^{ply}):=\sum_{i=1}^{K}\int_{z_0}^{z_1}||S_i(z|R^{ply},\alpha^{ply},\theta_i^{ply})-S_i^{tracked}(z)||_2^2dz, \tag{5}
$$
其中 K 是股的总数，$S_i$ 由公式（4）给出，$S_i^{tracked}$ 是第 $i$ 个输入的股的中心（图 5-d），其两个端点分别是 z0 和 z1。

![Figure 5](https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%205.png?raw=true "图 5")

**图 5：纱线几何形状的采集。** 

(a) 我们堆叠了多根纱线并对其进行 CT 扫描。 

(b) 其中一根扫描纱线的体积密度信息。 

(c) 提取的基于纤维的纱线表示。 

(d) 跟踪股中心。

------

为了最小化公式 (5)，我们使用了 Nelder-Mead Simplex Method [1965] ^[11]^的开源实现^[3]^。 人们还可以利用更高级的优化方法，例如浮点切线算法^[2]^，可能会带来更好的准确性和性能。 然而，由于我们的采集设置保持纱线样本笔直（图 5-a），输入曲线（即 $S_i^{tracked}$ ）已经接近一条圆形螺旋线。 我们发现我们的简单方法速度快且表现良好（即没有收敛问题），并且为渲染目的产生了高质量的结果。

#### 横截面估计（Cross-section estimation）

参照这篇文章^[14]^，我们将股的横截面建模为允许相交的椭圆，以模拟股的压缩。 给定一个横截面，我们在每个股的中心放置一个椭圆，其短轴指向由所有股中心形成的多边形的中心（参见图 6 中的 3 股的示例）。这些椭圆用于确定椭圆轴的长度（即 $e_X$ 和 $e_Y$ ）。 我们假设每个股是相同的，因此根据来自所有股的信息获得一组 $e_X$ 和 $e_Y$ 的值。 特别是，我们在平面中旋转和平移每个股（及其所有组成纤维中心），使其轴对齐并以原点为中心（图 6，右）。通过堆叠来自所有横截面的所有变换的股，^1^ 我们获得了由纤维中心组成的累积二维点云（图 7）。然后，我们将 $e_X$ 和 $e_Y$ 分别设置为所有这些点的 X 和 Y 坐标标准差的两倍。由此产生的椭圆覆盖了大约95%的纤维中心。我们依靠我们的飞散纤维模型来捕获剩余的大部分不规则的纤维。

除了股捻度和横截面参数外，我们估计每股的纤维数量为 $m=\lfloor L_{total}/L_{ply}K\rfloor$，其中 $L_{total}$ 表示测量几何形状中纤维的总长度（图 5-c），$L_{ply}$ 表示拟合层中心的长度（所有 $S_i$ 曲线具有相同的长度），K 是股数。

![Figure 6](https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%206.png?raw=true "图 6")

**图 6：拟合股横截面（以3股示例）。**

（左）我们在每条股的中心放置一个椭圆。 该椭圆的短轴指向由所有股中心形成的多边形的中心（显示为灰色并带有虚线边界）。 

（右）然后旋转和平移所有股以及相应的纤维点（平面内）。 然后，这些转换后的 2D 纤维位置信息将用于拟合股的横截面（图 7）。

------

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%207.png?raw=true" alt="Figure 7" title="图 7" style="zoom: 80%;" />

图 7：拟合股横截面（续）Fitting ply cross-sections (cont’d)。 

从一系列横截面中转换的纤维中心（图 6）的密度可视化情况。 我们使用此密度信息来确定股（ply）横截面的形状。

------

### 4.3 纤维分类（Fiber Classification）

使用 §4.2 中获得的合股信息，我们解开相互缠绕的股，并使它们都以 Z 轴为中心。 然后这些股中的所有纤维形成一个“纤维池”，将通过我们管线的以下步骤进行分析。 在这一步中，我们将这些纤维分为常规纤维和飞散纤维。

为了将每种纤维分为两类之一，我们考虑其到股中心（即 Z 轴）的最小和最大距离，分别表示为 $d_{min}$ 和 $d_{max}$。 给定具有 n 个顶点 $(x_1, y_1, z_1) ,. . . ,(x_n, y_n, z_n)$ 的纤维，我们有
$$
d_{min}:=\min_{1\leq i\leq n}||(x_i,y_i)||_2,\quad d_{max}:=\max_{1\leq i\leq n}||(x_i,y_i)||_2.
$$
真实纱线的 CT 测量值通常包含不属于纱线的外来成分（例如灰尘）。 它们可以通过较大的 $d_{min}$ 值来区分，因为外来材料往往远离股中心。 在实践中，我们认为所有 $d_{min}$ 超过某个阈值的纤维都是外来的，并简单地忽略它们。 然后，我们根据它们的 $d_{max}$ 值将剩余的纤维分为常规纤维和飞散纤维。 直观地说，具有较小 $d_{max}$ 值的纤维靠近帘股的中心，更可能是规则的。 另一方面，具有较大 $d_{max}$ 值的那些纤维在某个点离中心较远。 因此，它们被认为是飞散纤维。

为了稳定地获得分别用于识别外来纤维和飞散纤维的阈值，我们分别考虑了所有 $d_{min}$ 和 $d_{max}$ 值的平均值（表示为 $\mu_{min},\ \mu_{max}$）和标准差（表示为 $\sigma_{min},\ \sigma_{max}$）。 准确地说，我们将所有满足 $d_{min} > \mu_{min}+c_{min}\sigma_{min}$ 的纤维视为外来的，其余满足
$$
d_{max} > \mu_{max}+c_{max}\sigma_{max} \tag{6}
$$
的作为飞散纤维（其中 $c_{min}$ 和 $c_{max}$ 是用户指定的常数）。 在实践中，我们使用 $c_{min}=c_{max}=2$ 并对每个（解开的）股分别进行纤维的分类。 图 8 显示了一个分类的示例。

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%208.png?raw=true" alt="Figure 8" title="图 8" style="zoom:80%;" />

**图 8：纤维分类：**

我们将所有输入的纤维分为两类：常规纤维和飞散纤维（去除了外来物）。

 (a) 每根纤维的 $(d_{min},\ d_{max})$ 散布图。

 (b, c, d) 2D 纤维的可视化，其中水平轴和垂直轴分别表示每个纤维顶点的 $z_i$ 和 $||(x_i, y_i)||_2$。 虚线表示纤维被视为飞散纤维的阈值。

------

### 4.4 拟合纤维的分布和偏移（Fitting Fiber Distribution and Migration）

鉴于在 §4.3 中获得的一组常规纤维，现在介我们管线中的最后一步，它对纤维分布公式 （1） 和偏移公式 （3）的参数进行拟合。 回想一下，所有这些纤维都属于解开的股，这意味着它们都以 Z 轴为中心。

理论上，纤维偏移参数 $R_{min},\ R_{max},$ 和 $s,$ 可以从单个常规纤维中得到。 然而，由于实际数据的不规则性，仅使用一根纤维通常会产生非常不可靠的结果。 此外，由于 CT 成像处理步骤的限制，输入几何结构中的许多纤维都很短 ^[9]^，这使得偏移参数估计更具挑战性（更加困难）。

我们通过最小化重建误差来解决这个问题，它被定义为：
$$
E_{mig}(R_{min},\ R_{max},\ s)\\:=\sum_{i}\min_{R_i,\ \theta_i^{(0)}}E_i(R_i,\ \theta_i^{(0)}|R_{min},\ R_{max},\ s), \tag{7}
$$
在这里，求和针对所有常规的纤维，$E_i$ 表示纤维 $i$（表示为折线）与由 $R_i,\ θ^{(0)}_i,\ R_{min},\ R_{max},$  和 $s$ 通过公式（1）和公式（3）生成的螺旋线之间的平方 L2 差。即，
$$
E_i(R_i,\ \theta_i^{(0)}|R_{min},\ R_{max},\ s):=\int_{z}{||F_i(z)-\tilde{F}_i(z)||_2^2}dz,\tag{8}
$$
其中 $F_i$ 和 $\tilde{F}_i$ 分别表示输入和生成的纤维，两者都由 z 参数化。 这个一维积分的极限由 $F_i$ 的两个端点的 Z 坐标给出。 然后，设置我们$(R^∗_{min},\ R^∗_{max},\ s^∗)=arg\ min E_{mig}(R_{min},\ R_{max},\ s)$。

然而，最小化公式（7）中的重建误差并不简单，因为误差度量本身包括对 $R_i$ 和 $θ^{(0)}_i$ 的最小化。 因此，我们枚举了一组密集采样的 $R_{min},\ R_{max},$ 和 $s$ 值。 对于每个组合，我们解决内部优化问题（即等式（7）的 RHS（right-hand-side，右手边））。 类似于最小化公式 (5)，我们发现很容易为这个内部问题找到优化方法并使用相同的实现。

在确定纤维偏移参数后，只有横截面纤维分布还是未知的。 令 $R^∗_i$ 和 $θ^{(0)∗}_i$ 是对于每个纤维 $i$ 的 $E_i(R_i,\ \theta_i^{(0)}|R_{min},\ R_{max},\ s)$ 的最小值。 然后，我们对所有 $R^*_i$ 值应用最大似然估计 (MLE) 以获得纤维分布参数 $\epsilon$ 和 $\beta$。 请注意，密度函数即公式 (1) 本质上是有条件的，因为它在 $R$ 不是均匀分布的拒绝采样框架（算法 2）中使用。 MLE 的无条件密度应为：
$$
p^{MLE}(R)=2Rp(R)=2R[(1-2\epsilon)(\frac{e-e^R}{e-1})^\beta+\epsilon].\tag{9}
$$
令 $q(\epsilon,\ \beta)$ 为公式（9）的归一化项
$$
q(\epsilon,\ \beta):=\int^1_0{p^{MLE}(R)}dR,\tag{10}
$$
我们有可以在 MLE 中使用的归一化密度函数 $p^{MLE}_{norm}(R|\epsilon,\beta):=p^{MLE}(R)/q(\epsilon,\beta)$。 在实践中，我们使用 Matlab 的 mle() 函数，对 $q$ 进行数值评估，这有时容易出现（数值相似）局部最优。 然而，这在我们的实验中并没有造成视觉上的差异。

至此，我们已经获得了一组基于股和基于纤维的参数，可用于在程序上生成规则的纤维曲线。 然而，仅使用常规纤维，纱线看起来不够真实，因为它们没有不规则性。 在下一节中，我们将在 §5.1 中介绍他们改进的飞散纤维模型，在 §5.2 中，我们将描述如何根据在 §4.3 中获得的真实飞散纤维来拟合模型参数。

## 5 我们的飞散纤维模型（Our Flyaway Fiber Model）

天然布料的纱线通常含有偏离大多数其他纤维的飞散纤维，导致纱线的微观几何形状非常不规则。 尽管与普通纤维相比，飞散纤维要少得多，但它们对织物的绒毛性有很大影响。 因此，要准确再现现实世界织物的外观和结构，需要对这些纤维进行适当建模。

### 5.1 模型描述（Model Description）

纺织品研究人员已经研究了飞散纤维。 特别是 Voborova 等人^[17]^将飞散纤维分为了五种类型。 受他们工作的启发，我们引入了一种改进的飞散纤维模型，而不是 Schroder 等人^[14]^基于 Perlin 噪声开发的模型。

我们的模型将飞散纤维分为两类：环（loop）和毛发（hair）（图 9）。 我们的毛发类型纤维对应于 Voborova 等人^[17]^的前两个飞散纤维类，而我们的环类型纤维对应于他们的第三类纤维。

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%209.png?raw=true" alt="Figure 9" title="图 9" style="zoom:80%;" />

**图 9：我们模型中的两种飞散纤维。**

------

#### 环类型（Loop-type）

环型飞散纤维在主股体内具有两个端点。 这些纤维中的每一个最初都是规则的，但其中一部分在制造过程中被意外拉出（图 9-a）。 这些纤维的密度和每个环偏离股中心的距离提供了一个重要的视觉提示，说明纤维的扭绞程度。

Schroder等人^[14]^没有明确模拟这些类型的纤维。 相反，他们使用非常强的纤维偏移来实现类似的效果。 不幸的是，这种方法不能轻易地捕获偶尔出现的环形纤维，而这种纤维在现实中实际上很常见。 其生成的几何图形结果通常包含定期出现的循环（图 10-a）。

我们通过修改之前构建的常规纤维（算法 1 的第 2 行）来生成环型飞散纤维。 当将常规纤维变成环形飞散纤维时，我们使用最大化的公式（3）随机选择其中一个顶点并将其半径提高到 $R^{loop}_{max}$（通过缩放其 X 和 Y 坐标）。 我们还放大了与其属于同一偏移周期的相邻顶点的半径（即公式（3）中的 $R_i(θ)$ 的一个周期，见图 11）。 为了创建一组环型飞散纤维（基于现有的常规纤维），我们从它们每个的正态分布中绘制 $R^{loop}_{max}$。

对于每一股，我们使用 $\rho^{loop}$ 来捕获环型纤维的密度。 给定一个以 $Z_0Z_1$ 为中心的解开的股，其中 $Z_0 = (0, 0, z_0) ,\ Z_1 = (0, 0, z_1)$ ，我们重复上述过程以生成 $\lfloor\rho^{loop}(z_1-z_0)\rfloor$ 范围的环型飞散纤维。

![Figure 10](https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%2010.png?raw=true "图 10")

**图 10：环型飞散纤维模型的比较：**

(a) 基于偏移的方法^[14]^缺乏表示偶尔发生的环形纤维的通用性；

(b) 我们的模型具有足够的代表能力来捕捉这种纤维几何形状。

------

![Figure 11](https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%2011.png?raw=true "图 11")

图 11：环型飞散纤维的生成。 

(a) 我们随机选择一个顶点，最大化到股中心的距离（用橙色圆圈表示）。

(b) 然后我们选择属于同一偏移周期的所有顶点（以绿色显示）并缩放它们的半径，以便选定的顶点之后具有半径 $R^{loop}_{max}$。

------

#### 毛发类型（Hair-type）

如图 9-b 所示，每根毛发类型的飞散纤维在其股的主体之外都有一个端点。 这种类型的纤维对纱线毛茸茸的外观贡献最大。 我们通过显式添加其可见（飞散）部分来创建毛发类型纤维（用于算法 1 的第 3 行）。 也就是说，我们生成一个由其起始和结束半径 $R^{hair}_{min},\ R^{hair}_{max}$（即到股中心的距离），方位角 $θ^{hair}_{min},\ θ^{hair}_{max}$ 以及位置 $z^{hair}_{min},\ z^{hair}_{max}$ 确定的“弧” 。 设 $R^{hair}_{span}:=R^{hair}_{max} − R^{hair}_{min},\ θ^{hair}_{span} := θ^{hair}_{max} − θ^{hair}_{min}\ and\ z^{hair}_{span} := z^{hair}_{max} − z^{hair}_{min}$，由 t  ∈ [0, 1] 参数化的毛发型飞散纤维可以表示为
$$
x^{hair}(t)=R^{hair}(t)\cos[\theta^{hair}(t)],\\
y^{hair}(t)=R^{hair}(t)\sin[\theta^{hair}(t)],\\
z^{hair}(t)=z^{hair}_{min}+z^{hair}_{span}t,\tag{11}
$$
其中 $R^{hair}(t)=R^{hair}_{min}+R^{hair}_{span}t\ and\ \theta^{hair}(t)=\theta^{hair}_{min}+\theta^{hair}_{span}t$。

为了在具有端点 z0 和 z1 的公共中心周围生成一组毛发类型纤维，对于每一根纤维我们在 $U[z_0, z_1]$ 范围内绘制 $z^{hair}_{min}$ 并在 $U[0, 2π)$ 范围内绘制 $θ^{hair}_{min}$。 其他参数 $R^{hair}_{min},\ R^{hair}_{span},\ θ^{hair}_{span}$ 和 $z^{hair}_{span}$ 是从单独的正态分布中采样的。 与环类型纤维类似，我们使用 $\rho^{hair}$ 来描述毛发类型纤维的密度。

在Schroder 等人的文章中^[14]^，毛发类型纤维是通过随机添加受 3D Perlin 噪声干扰的切线方向的短曲线生成的（图 12-c）。 虽然能够生成类似毛发的纤维，但这种方法过于简单化，使其难以与现实匹配，更重要的是，难以拟合给定的测量纱线的几何形状。 另一方面，我们的模型具有明确的统计意义并且易于拟合（参见 §5.2）。

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%2012.png?raw=true" alt="Figure 12" title="图 12" style="zoom:80%;" />

**图 12：飞散纤维模型（毛发类型）的比较：**

(a) 测量的纱线几何形状（基本事实）； 

(b) 无飞散纤维的程序化纱线； 

(c) 具有基于 Perlin 噪声的飞散纤维的程序化纱线^[14]^; 

(d) 使用我们的模型生成的具有飞散纤维的程序化纱线。 

其中（c）增加了纤维偏移以模拟环类型纤维效果。

------

#### 纤维扰动（Fiber perturbations）

在此之前，所有常规和飞散的纤维都是非常光滑的曲线。 这种平滑度在现实中很少存在：真正的纤维通常包含许多小的但不规则的弯曲。 为了模拟这种效果我们通过随机缩放每个顶点的半径（即 X 和 Y 坐标）向所有纤维添加微小扰动。

#### 探讨（Discussion）

我们的飞散纤维模型做了两个显著的简化。 特别是，我们的环型飞散纤维总是“跨越”一个迁移周期（如图 11 所示），而实际情况通常并非如此。 此外，由于公式（11）我们的毛发类型飞散纤维都具有“弧形”形状，而真正的毛发型纤维通常具有更复杂的轨迹（图 13）。 尽管有这些简化我们还是很好地匹配了纱线的整体外观（见图 15）。 引入它们是为了确保的模型可以从包含有限数量的飞散纤维的测量数据中可靠地拟合（例如，图 5-b）。 未来，随着测量量的增加，可以设计基于更复杂的统计分布的飞散纤维模型。

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%2013.png?raw=true" alt="Figure 13" title="图 13" style="zoom:80%;" />

**图 13：我们的毛发类型飞散纤维模型所做的简化：**

（顶部）我们的毛发类型飞散纤维都是弧形的； 

（底部）真正的毛发型纤维具有更复杂的轨迹。

------

### 5.2 模型拟合（Model Fitting）

回想一下，在 §4.3 中，来自解开的股的纤维被分为常规纤维和飞散纤维。 鉴于我们的飞散纤维模型（§5.1），现在描述如何拟合模型参数，即 $\rho^{hair},\ R^{hair}_{min},\ R^{hair}_{span},\ z^{hair}_{span}$ 和毛发类型的 $θ^{hair}_{span}$，以及用于循环类型的 $\rho_{loop}$ 和 $R^{loop}_{max}$ 。 请注意，$z^{hair}_{min}$ 和 $θ^{hair}_{min}$ 没有拟合，因为我们在生成过程中对它们进行了均匀采样。

在获得每条解开股的飞散纤维后，我们通过识别每根纤维的环类型和毛发类型部分开始拟合过程。 如图 14-a 所示，一根飞散纤维可以包含两种成分。 因此，对于它们中的每一个，我们首先检查其任何端点的半径（即 $||(x, y)||_2$）是否高于飞散阈值公式 (6) 。 如果是，我们在半径处于局部最小值且低于阈值的顶点处切断纤维的相应端点，并将其添加到毛发型飞散纤维的集合中。 然后将剩余部分（如果有的话）添加到环类型纤维的集合中。 这种纤维分离操作如图 14-b 所示。

<img src="https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%2014.png?raw=true" alt="Figure 14" title="图 14" style="zoom:80%;" />

**图 14：处理飞散纤维。 **

(a) 一根纤维可以同时包含毛发类型和环类型成分。 

(b) 我们将每根飞散的纤维分成多个毛发类型和环类型。

------

在处理完所有纤维后，我们使用相应纤维的数量除以解开的股的长度（即 $z_1 -z_0$）来获得飞散纤维的密度 $\rho^
{loop}$ 和 $\rho^{hair}$。 然后，对于每个环类型纤维，我们计算其所有顶点的半径并将 $R^{loop}_{max}$ 设置为最大值。 类似地，可以通过检查每个头发类型纤维的顶点来评估 $R^{hair}_{min},\ R^{hair}_{span},\ \theta^{hair}_{span},\ z^{hair}_{span}$。 然后，我们计算每个量的样本均值和标准差，这些数据可通过公式（11）生成毛发类型纤维。

拟合飞散纤维的参数后，我们终于恢复了表 1 中所有参数的值。使用算法 1，现在可以生成逼真的纱线几何形状，而无需繁琐的 CT 测量。

## 6 结果（Results）

我们通过三个显微 CT 扫描测量了九个真实世界纱线的微观几何形状。 这些纱线由棉（cotton）、人造丝（rayon）、丝绸（silk）和涤纶（polyester）制成，是常用纱线材料的良好样本。 我们的采集设置如图 5-a 所示。 所有纱线都在 XRadia MicroXCT 扫描仪中以 2.5 µm 的分辨率进行扫描，每次扫描大约需要三个小时。 所有渲染图像都是使用基于 Mitsuba 物理渲染器的修改版本创建的^[6]^。

### 性能（Performance）

我们的拟合算法速度很快：给定经过处理的 CT 数据（图 5-cd），拟合每根纱线只需不到十分钟的 CPU 内核时间。 与通常需要几个核心小时的 CT 数据处理步骤 (§4.1) 相比，我们的拟合成本可以忽略不计。 我们的方法通常表现良好：尽管存在非凸优化（例如，§4.4），但我们没有观察到由局部最小值引起的任何视觉差异。

### 验证（Validation）

图 15 显示了我们所有测量的纱线几何形状 (a) 和我们的拟合结果 (b)。 用我们的方法生成的程序化纱线紧密地捕捉了测量几何形状的统计数据，传达了对相应纱线类型的令人信服的表现。 为了验证这一点，我们将模型的完整渲染图 (d) 与这些纱线的照片 (c) 进行了比较。 为了描述我们生成的程序化纱线的光学特性，我们使用了 Khungurn 引入的纤维散射模型^[9]^。 对应的参数值见表 3。 请注意，我们的模型有时会显得稍微不毛茸茸一些，因为我们测量的几何形状 (a) 来自小的（大约 0.5 厘米长）纱线段，可能无法捕捉到照片的所有不规则性。 但这不是我们方法的限制，因为可以扫描同一类型纱线的多个副本以提供多样性并将所有信息提供给我们的参数拟合算法。

### 非重复纱线（Non-repetitive yarns）

图 16 显示了使用我们的方法生成的长纱线。 与许多现有的微外观模型^[9][20]^相比，我们的方法不依赖于复制（即平铺）小块织物。 因此，我们产生了真实的、非重复的细节。

### 完整的纺织品（Full textiles）

为了描述完整的纺织品，现有的微外观模型通常需要数十兆字节（基于纤维）或数千兆字节（基于体积）的数据。然而，我们的程序化模型表示非常小巧：在使用算法 1 实例化纤维之前，只需为每种类型的纱线存储 22 个数字（见表 2）。通过将这些分布参数与一组稀疏的纱线中心曲线相结合，可以生成细节丰富的纺织品模型。这在图 17 中得到了证明，其中 (a) 列显示了我们用于填充纤维级结构的纱线曲线。^2^ 如果没有这些小尺度细节，渲染质量就会很有限。另一方面，通过添加微观几何形状，纺织品看起来更加逼真（b）。我们的方法构建的模型是完全程序化的，并且提供了简单的可编辑性。这在图 17 的 (c) 列中得到了证明。特别是对于丝绸场景，我们调整了纤维捻度，使纤维能够更好地对齐。这种纤维级别的修改不仅会导致明显更强的各向异性高光，还会导致织物变得不那么透明（这可以从地面上更暗的阴影中看出）。这是因为当纤维更好地对齐时，它们往往会通过更少的“间隙”更有效地阻挡光线。图 17 中的第二个示例显示了改变飞散纤维的分布如何影响全局织物的整体外观。通过增加飞散纤维的密度，整个布料变得更加有毛绒感，导致结构上的高光更少，但出现更多小的随机亮点或“闪光”。图 17 中的最后一个结果是均匀的编织篮。我们使用改变了光学参数的“聚酯纤维（涤纶） 1”的程序化几何形状。当使股的横截面的形状更偏向椭圆 (c) 时，下面的纤维结构会发生巨大变化，从而导致整体光泽度降低。这进一步证明了我们方法的多功能性以及精确拟合模型参数的重要性。

### 限制和未来的工作（Limitations and future work）

我们的拟合管线需要解决几个非凸优化问题（§4.4）。 未来，可以探索先进的求解技术，以获得更好的数值精度和性能。 目前，用我们的模型表示的纱线渲染纺织品需要实现所有纤维（使用算法 1）。 我们打算开发直接在我们的程序化几何上工作的高效渲染算法。 此外，我们的纱线模型做了一些简化假设：

* 假定股横截面是椭圆的并且在空间上是不变的，这导致图 15-ab 中的人造丝（Rayon） 3、丝绸（Silk） 1 和丝绸（Silk） 2 的几何不匹配；
* 飞散纤维具有相对简化的形状（在 §5.1 中讨论）。

因此，纱线模型的进一步推广和开发相应的拟合技术将是有价值的。 最后，我们的方法可以捕获的几何差异级别受到微型 CT 扫描仪可以采用的最大样本量的限制。 因此，我们的模型中缺少难以测量的大的纱线级别的差异。

![Figure 15](https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%2015.png?raw=true "图 15")

**图 15：参数拟合结果。 **

(a) CT 测量的纱线几何形状。 

(b) 使用我们的方法拟合的程序化纱线几何形状。 

(c) 真实世界纱线的照片。 

(d) 在类似的照明/观看条件下，我们的程序化纱线的完整效果图。 我们的拟合参数值如表 2 所示。

------

![Figure 16](https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%2016.png?raw=true "图 16")

**图 16：使用我们的拟合参数程序化生成的长织物纱线。 **

从上到下分别为“棉（Cotton） 2”（原始参数）、“人造丝（Rayon） 1”（原始参数）和“人造丝（Rayon） 4”（增加绒毛感）。 与许多先前的微观外观建模技术不同，我们的模型不依赖平铺，因此可以提供高质量、非重复的纱线几何形状。

------

![Figure 17](https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Figure%2017.png?raw=true "图 17")

**图 17：使用我们的方法通过程序化添加的具有纤维级几何形状的完整纺织品。 **

三行中使用的原始参数是：“丝绸（Silk） 1”+“丝绸（Silk） 2”（第一行），“人造丝（Rayon） 3”+“人造丝（Rayon） 4”（第二行）和  “涤纶（Polyester） 1”（第三行）。 编辑后的丝绸示例是通过将股数和纤维捻度（即 $\alpha^{ply}$ 和 $\alpha$）乘以 10 倍获得的。 修改后的人造丝模型是由三倍的飞散密度 $\rho^{loop}$ 和 $\rho^{hair}$ 以及双倍的 $R^{loop}_{max}$ 和 $R^{hair}_{span}$ 产生的。 改变的聚酯示例是通过将 $e_Y$（椭圆的短轴）减半，同时将 $e_X$（长轴）加倍来创建的。

------

![Table 2](https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Table%202.png?raw=true "表 2")

**表 2：图 15 中显示的所有结果的拟合参数值。**

正和负的 $\alpha$ 值分别表示逆时针和顺时针的（股/纤维）加捻。 不失一般性，我们假设 $R_{max}=1$。对于飞散分布参数，括号中的成对数字表示相应正态分布的均值和标准差。 当使用算法 1 生成纱线时，此处未提及的所有参数（例如，$R_i,\ \theta_i,\ \theta^{(0)}_i$ ）都是从它们的域中均匀提取的。

------

![Table 3](https://github.com/Orznijiang/MyImageBed/blob/main/Paper-Reading/Rendering/Fabric/Fitting%20Procedural%20Yarn%20Models%20for%20Realistic%20Cloth%20Rendering/Table%203.png?raw=true "表 3")

**表 3：使用 Khungurn 等人^[9]^引入的用于生成图 15 中的所有渲染效果的模型的纤维散射参数。**

我们手动调整了参数值，因为自动找到最佳参数值与我们当前的工作正交（无关）。 为了更好的外观匹配，我们推荐使用先进的逆向渲染技术，例如 Khungurn 的技术^[9]^。

------

## 7 结论（Conclusion）

对于许多设计、原型制作和娱乐应用来说，对织物外观进行准确建模非常重要。 为了准确匹配现实，先前的微观外观模型要么依赖于数据密集型的数据集，要么需要复杂的手动参数调整。 我们引入了一种弥补这一差距的技术，从而在避免它们的弱点的同时享受两个方法的优点。 我们的方法自动将程序化纱线模型拟合到使用体积成像获得的准确物理测量值。 由此产生的模型，每种纱线类型仅包含 22 个浮点数，可用于合成具有高视觉质量且没有重复图案的大型纺织品。 这些模型的统计意义也允许直观的编辑。

## 致谢（Acknowledgments）

我们感谢 Pramook Khungurn 分享他的纤维提取工具（第 4.1 节）。 我们感谢 Kai Schroder 的有益讨论，并感谢他分享了他对程序化纱线生成的实现（算法 1）。 这项工作的资金由美国国家科学基金会 (IIS 1513967) 提供。


## 参考文献

* [1] CIRIO, G., LOPEZ-MORENO, J., MIRAUT, D., AND OTADUY, M. A. 2014. Yarn-level simulation of woven cloth. ACM Trans. Graph. 33, 6, 207:1–207:11.
* [2] DEROUET-JOURDAN, A., BERTAILS-DESCOUBES, F., AND THOLLOT, J. 2013. Floating tangents for approximating spatial curves with G1 piecewise helices. Computer Aided Geometric Design 30, 5, 490–520.
* [3] HUTT, M., 2011. C++ implementation of the Nelder-Mead simplex method. http://www.mikehutt.com/neldermead.html.
* [4] IRAWAN, P., AND MARSCHNER, S. 2012. Specular reflection from woven cloth. ACM Trans. Graph. 31, 1, 11:1–11:20.
* [5] JAKOB, W., ARBREE, A., MOON, J. T., BALA, K., AND MARSCHNER, S. 2010. A radiative transfer framework for rendering materials with anisotropic structure. ACM Trans. Graph. 29, 4, 53:1–53:13.
* [6] JAKOB, W., 2013. Mitsuba renderer. http://www.mitsubarenderer.org.
* [7] KALDOR, J. M., JAMES, D. L., AND MARSCHNER, S. 2008. Simulating knitted cloth at the yarn level. ACM Trans. Graph. 27, 3, 65:1–65:9.
* [8] KEEFE, M. 1994. Solid modeling applied to fibrous assemblies. Part I: Twisted yarns. Journal of the Textile Institute 85, 3, 338– 349.
* [9] KHUNGURN, P., SCHROEDER, D., ZHAO, S., BALA, K., AND MARSCHNER, S. 2015. Matching real fabrics with microappearance models. ACM Trans. Graph. 35, 1, 1:1–1:26.
* [10] MORRIS, P., MERKIN, J., AND RENNELL, R. 1999. Modelling of yarn properties from fibre properties. Journal of the Textile Institute. Part 1, Fibre science and textile technology 90, 3, 322– 335.
* [11] NELDER, J. A., AND MEAD, R. 1965. A simplex method for function minimization. The computer journal 7, 4, 308–313.
* [12] POINTCARRE, 2016. Pointcarre textile software.    http://www.pointcarre.com.
* [13] SADEGHI, I., BISKER, O., DE DEKEN, J., AND JENSEN, H. W.2013. A practical microcylinder appearance model for cloth rendering. ACM Trans. Graph. 32, 2, 14:1–14:12.
* [14] SCHRODER  , K., ZINKE, A., AND KLEIN, R. 2015. Image-based reverse engineering and visual prototyping of woven cloth. Visualization and Computer Graphics, IEEE Transactions on 21, 2,188–200.
* [15] SHINOHARA, T., TAKAYAMA, J.-Y., OHYAMA, S., ANDKOBAYASHI, A. 2010. Extraction of yarn positional information from a three-dimensional CT Image of textile fabric using yarn tracing with a filament model for structure analysis. Textile Research Journal 80, 7, 623–630.
* [16] TAO, X. 1996. Mechanical properties of a migrating fiber. Textile research journal 66, 12, 754–762.
* [17] VOBOROVA, J., GARG, A., NECKAR, B., AND IBRAHIM, S. 2004. Yarn properties measurement: an optical approach. In 2nd International textile, clothing and design conference, 1–6.
* [18] XU, Y.-Q., CHEN, Y., LIN, S., ZHONG, H., WU, E., GUO, B., AND SHUM, H.-Y. 2001. Photorealistic rendering of knitwear using the lumislice. In Proceedings of the 28th Annual Conference on Computer Graphics and Interactive Techniques, ACM, 391–398.
* [19] YUKSEL, C., KALDOR, J. M., JAMES, D. L., AND MARSCHNER, S. 2012. Stitch meshes for modeling knitted clothing with yarnlevel detail. ACM Trans. Graph. 31, 3, 37:1–37:12.
* [20] ZHAO, S., JAKOB, W., MARSCHNER, S., AND BALA, K. 2011. Building volumetric appearance models of fabric using micro CT imaging. ACM Trans. Graph. 30, 4, 44:1–44:10.
* [21] ZHAO, S., JAKOB, W., MARSCHNER, S., AND BALA, K. 2012. Structure-aware synthesis for predictive woven fabric appearance. ACM Trans. Graph. 31, 4, 75:1–75:10.
* [22] ZHAO, S., HASAN ˇ , M., RAMAMOORTHI, R., AND BALA, K. 2013. Modular flux transfer: Efficient rendering of high-resolution volumes with repeated structures. ACM Trans. Graph. 32, 4, 131:1– 131:12.







