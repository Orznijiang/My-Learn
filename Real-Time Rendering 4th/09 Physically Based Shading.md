# Chapter 9 基于物理的着色（Physically Based Shading）

## 9.10 布料的BRDF模型（BRDF Models for Cloth）

布料往往具有不同于其他类型材料的微观几何形状。 根据织物类型，它可能具有高度重复的编织微结构、从表面垂直突出的圆柱体（cylinders）（线（threads）），或两者兼而有之。 因此，布料表面具有与众不同的表现，通常需要专门的着色模型，例如各向异性镜面高光（anisotropic specular highlights）、粗糙散射（asperity scattering） ^[919]^（光通过突出的半透明纤维散射引起的明亮边缘效应），甚至颜色随观察方向的变化（ 由穿过织物的不同颜色的线引起）。

除 BRDF 之外，大多数织物都具有高频空间变化，这也是创造令人信服的布料外观的关键 ^[825]^。 请参见图 9.42。

![Figure 9.42](https://github.com/Orznijiang/MyImageBed/blob/main/Real-Time%20Rendering%204th/Chapter%2009/Figure%209.42.png?raw=true "图 9.42")

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

Ashikhmin 等人 ^[78]^ 提出使用倒置高斯 NDF （normal distribution function）对天鹅绒（velvet）进行建模。 该 NDF 在之后的工作中稍作修改了 ^[81]^，还提出了一种微平面 BRDF 的变体形式，用于一般的材料建模，没有遮蔽阴影（masking-shadowing）项，但修改了分母。

游戏 《秩序：1886》（The Order : 1886） ^[1266]^ 中使用的布料 BRDF 将来自 Ashikhmin 和 Premoze 后来的报告 ^[81]^ 中修改后的微平面 BRDF 和天鹅绒 NDF 的广义形式，与公式 9.63 中的漫反射项进行结合。 广义天鹅绒的 NDF 项是
$$
D(m)=\frac{\chi^+(\mathbf{n},\mathbf{m})}{\pi(1+k_{amp}\alpha^2)}(1+\frac{k_{amp}exp(\frac{(\mathbf{n},\mathbf{m})^2}{\alpha^2((\mathbf{n},\mathbf{m})^2-1)})}{(1-(\mathbf{n},\mathbf{m})^2)^2}),\tag{9.73}
$$
其中 $α$ 控制反转高斯（inverted Gaussian）的宽度，而 $k_{amp}$ 控制其振幅（amplitude）。 完整的布料 BRDF 是

$$
f(\mathbf{l},\mathbf{v})=(1-F(\mathbf{h},\mathbf{l}))\frac{\rho_{ss}}{\pi}+\frac{F(\mathbf{h},\mathbf{l})D(\mathbf{h})}{4(\mathbf{n}\cdot\mathbf{l}+\mathbf{n}\cdot\mathbf{v}-(\mathbf{n}\cdot\mathbf{l})(\mathbf{n}\cdot\mathbf{v}))}.\tag{9.74}
$$
在游戏 《神秘海域4》（Uncharted 4）^[825]^ 中使用了上面这种 BRDF 的一种变体，用于处理粗糙的织物，例如羊毛（wool）和棉花（cotton）。

Imageworks ^[947]^ 使用不同的倒置 NDF 来表示光泽项，其可以添加到任何 BRDF 中：
$$
D(m)=\frac{\chi^+(\mathbf{n}\cdot\mathbf{m})(2+\frac{1}{\alpha})(1-(\mathbf{n}\cdot\mathbf{m})^2)^{\frac{1}{2\alpha}}}{2\pi}.\tag{9.75}
$$
尽管该 NDF 的 Smith 遮蔽阴影（masking-shadowing）函数没有封闭形式的解，但 Imageworks 能够用一个解析函数（analytical function）逼近其数值解。 Estevez 和 Kulla ^[442]^ 讨论了**关于遮蔽阴影函数**和**光泽项与 BRDF 其余部分之间的能量守恒**的细节。 有关使用 Imageworks 光泽项渲染的一些示例，请参见图 9.43。

![Figure 9.43](https://github.com/Orznijiang/MyImageBed/blob/main/Real-Time%20Rendering%204th/Chapter%2009/Figure%209.43.png?raw=true "图 9.43")

**图 9.43 Imageworks 光泽镜面反射项添加到红色漫反射项。**

 从左到右，光泽粗糙度值为 $α = 0.15,0.25,0.40,0.65,$ 和 $1.0$。（图由 Alex Conty ^[442]^ 提供。）

------

到目前为止，我们看到的每种布料模型都仅限于特定类型的织物。 下一节中讨论的模型试图以更一般的方式对布料进行建模。

### 9.10.3 微圆柱布料模型

用于布料的微圆柱模型与用于头发的模型非常相似，因此 第 14.7.2 节 中对头发模型的讨论可以提供额外的背景信息。 这些模型背后的想法是假设表面被一维线（one-dimensional lines）所覆盖。 Kajiya 和 Kay 为这个情况 ^[847]^ 开发了一个简单的 BRDF 模型，Banks ^[98]^ 为它提供了坚实的理论基础。 因此它也被称为 Kajiya-Kay BRDF 或 Banks BRDF。 该概念基于以下观察：由一维线组成的表面在任何给定位置具有无限数量的法线，由垂直于**该位置的切向量 $t$ **的法线平面定义。 尽管已经基于这个框架开发了许多更新的微圆柱模型，但由于其简单性，原始的 Kajiya-Kay 模型仍然有一些用途。 例如，在游戏 《神秘海域4》（Uncharted 4）^[825]^ 中，Kajiya-Kay BRDF 被用于光泽织物（如丝绸（silk）和天鹅绒（velvet））的镜面反射（specular）项。

Dreamworks ^[348][1937]^ 使用相对简单且易由艺术家控制的微圆柱模型来制作织物。 纹理可用于改变粗糙度（roughness）、颜色（color）和线方向（thread direction），线方向可以指向表面的平面之外，用于对天鹅绒（velvet）和类似织物进行建模。 可以为织物的经线（warp）和纬线（weft）设置不同的参数，以模拟复杂的变色织物，例如闪光丝（shot silk）。 该模型被归一化为以达到能量守恒的目的。

Sadeghi 等人 ^[1526]^ 提出了一种基于对织物样品（fabric sample）和单根线（individual threads）的测量的微圆柱模型。 该模型还考虑了线之间的线间（inter-thread）遮蔽（masking）和阴影（shadowing）。

在某些情况下，实际上的头发 BSDF 模型（第 14.7 节）会用于布料。 RenderMan 的 PxrSurface 材料 ^[732]^ 有一个“绒毛（fuzz）”波瓣，它使用 Marschner 等人 ^[1128]^（第 14.7 节）的头发模型中的 **R** 项。 Wu 和 Yuksel ^[1924][1926]^ 在实时布料渲染系统中实现的模型之一源自迪士尼用于动画电影 ^[1525]^ 中的头发模型。



## 符号和定义

* $x^+$：将 $x$ 钳制为 $0$（非负）
* $x^\mp$：将 $x$ 钳制到 $0\leq x\leq 1$



## 参考文献

* [78] Ashikhmin, Michael, Simon Premoˇze, and Peter Shirley, “A Microfacet-Based BRDF Generator,” in SIGGRAPH ’00: Proceedings of the 27th Annual Conference on Computer Graphics and Interactive Techniques, ACM Press/Addison-Wesley Publishing Co., pp. 67–74, July 2000. Cited on p. 328, 335, 357
* [81] Ashikhmin, Michael, and Simon Premoˇze, “Distribution-Based BRDFs,” Technical Report, 2007. Cited on p. 357
* [98] Banks, David, “Illumination in Diverse Codimensions,” in SIGGRAPH ’94: Proceedings of the 21st Annual Conference on Computer Graphics and Interactive Techniques, ACM, pp. 327– 334, July 1994. Cited on p. 359
* [214] Burley, Brent, “Physically Based Shading at Disney,” SIGGRAPH Practical Physically Based Shading in Film and Game Production course, Aug. 2012. Cited on p. 325, 336, 340, 342, 345, 353, 354, 357, 364
* [348] Deshmukh, Priyamvad, Feng Xie, and Eric Tabellion, “DreamWorks Fabric Shading Model: From Artist Friendly to Physically Plausible,” in ACM SIGGRAPH 2017 Talks, article no. 38, July 2017. Cited on p. 359
* [442] Estevez, Alejandro Conty, and Christopher Kulla, “Production Friendly Microfacet Sheen BRDF,” Technical Report, Sony Imageworks, 2017. Cited on p. 358
* [631] Hable, John, “Uncharted 2: Character Lighting and Shading,” SIGGRAPH Advances in Real-Time Rendering in Games course, July 2010. Cited on p. 357, 635
* [732] Hery, Christophe, and Junyi Ling, “Pixar’s Foundation for Materials: PxrSurface and PxrMarschnerHair,” SIGGRAPH Physically Based Shading in Theory and Practice course, Aug. 2017. Cited on p. 321, 343, 359, 363, 364, 370
* [825] Jiang, Yibing, “The Process of Creating Volumetric-Based Materials in Uncharted 4,” SIGGRAPH Advances in Real-Time Rendering in Games course, July 2016. Cited on p. 356, 357, 358, 359
* [847] Kajiya, James T., and Timothy L. Kay, “Rendering Fur with Three Dimensional Textures,” Computer Graphics (SIGGRAPH ’89 Proceedings), vol. 17, no. 3, pp. 271–280, July 1989. Cited on p. 359, 642
* [919] Koenderink, Jan J., and Sylvia Pont, “The Secret of Velvety Skin,” Journal of Machine Vision and Applications, vol. 14, no. 4, pp. 260–268, 2002. Cited on p. 356
* [947] Kulla, Christopher, and Alejandro Conty, “Revisiting Physically Based Shading at Imageworks,” SIGGRAPH Physically Based Shading in Theory and Practice course, Aug. 2017. Cited on p. 321, 336, 343, 346, 347, 352, 353, 358, 363, 364
* [1128] Marschner, Stephen R., Henrik Wann Jensen, Mike Cammarano, Steve Worley, and Pat Hanrahan, “Light Scattering from Human Hair Fibers,” ACM Transactions on Graphics (SIGGRAPH 2003), vol. 22, no. 3, pp. 780–791, 2000. Cited on p. 359, 640, 641, 642, 643, 644
* [1266] Neubelt, D., and M. Pettineo, “Crafting a Next-Gen Material Pipeline for The Order: 1886,” SIGGRAPH Physically Based Shading in Theory and Practice course, July 2013. Cited on p. 357, 365, 370
* [1525] Sadeghi, Iman, Heather Pritchett, Henrik Wann Jensen, and Rasmus Tamstorf, “An Artist Friendly Hair Shading System,” in ACM SIGGRAPH 2010 Papers, ACM, article no. 56, July 2010. Cited on p. 359, 644
* [1526] Sadeghi, Iman, Oleg Bisker, Joachim De Deken, and Henrik Wann Jensen, “A Practical Microcylinder Appearance Model for Cloth Rendering,” ACM Transactions on Graphics, vol. 32, no. 2, pp. 14:1–14:12, Apr. 2013. Cited on p. 359
* [1924] Wu, Kui, and Cem Yuksel, “Real-Time Fiber-Level Cloth Rendering,” Symposium on Interactive 3D Graphics and Games, Mar. 2017. Cited on p. 359
* [1926] Wu, Kui, and Cem Yuksel, “Real-Time Cloth Rendering with Fiber-Level Detail,” IEEE Transactions on Visualization and Computer Graphics, to appear. Cited on p. 359
* [1937] Xie, Feng, and Jon Lanz, “Physically Based Shading at DreamWorks Animation,” SIGGRAPH Physically Based Shading in Theory and Practice course, Aug. 2017. Cited on p. 336, 359, 364