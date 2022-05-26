# 基于薄织物的多尺度混合微外观建模和实时渲染（Multi-Scale Hybrid Micro-Appearance Modeling and Realtime Rendering of Thin Fabrics）

## 摘要

微外观模型可以为布料渲染提供最先进的渲染质量。 不幸的是，它们通常情况下使用数据密度极大的 3D 或纤维网格来表示，这导致高细节程度的布料模型的渲染成本很高，无法做到实时渲染。 另一方面，传统的基于表面的模型是非常轻量级的，因此渲染速度很快。但是其通常缺乏对设计和原型相关的应用程序来说非常重要的保真度和细节。 这篇文章引入了一种多尺度混合模型来弥补薄织物在基于表面的渲染模型与基于微外观的渲染模型方面的细节差距。 这个多尺度混合模型同时继承了传统的基于表面的模型带来的渲染的快速性和微外观模型带来的丰富细节。 此外，这篇文章提出了一种新算法，将最先进的微外观模型表示转换为一种新的表示，同时定性地保留细节外观，同时通过将这种多尺度混合模型和新的表示方法集成到实时渲染系统中来证明这种技术的有效性。



## 1 介绍

布料材质的渲染是高保真渲染中的一个重要部分，它在我们的日常生活中很重要，且经常被运用与计算机图形场景中。此外，准确的布料外观对于纺织品的设计以及制造产业相关的应用来说至关重要。

布料外观的传统建模方法是基于表面的表示方法，例如专门化的BRDF表示^[1][2]^。这些模型通常具有轻量化、渲染速度快的特点，并且能够在远处观察织物时提供一个令人信服的结果，而无法在从近处观察时看到单根的纱线。不幸的是，这些模型缺乏在特写视图中生成逼真结果所需的细粒度细节，而这对于设计和虚拟现实中的许多应用程序来说很重要。

微外观布料模型 ^[3][4][5][6][7]^ 通过明确地将织物的细节结构捕获到纤维级别来为渲染提供卓越的质量。 这些微观几何形状通常使用高分辨率体积或纤维网格来描述。 由于存在纤维级细节，即使非常仔细地观察，这些模型仍然非常逼真。 与基于表面的模型相比，微外观模型通常存在数据密集性且渲染的成本很高。 即使预先进行大量的预计算，使用这些模型渲染来单个图像也可能在 CPU ^[8]^ 上花费几分钟，在 GPU ^[9]^ 上花费数十秒。

在本文中，我们通过引入用于薄织物的多尺度混合微观外观模型来弥合这两种技术之间的差距。 我们的模型同时具有传统基于表面的模型提供的轻量级和渲染快速的特点以及微观外观模型提供的高保真度和丰富细节的特点。 与现有技术相比，我们的方法具有以下优势。 首先，与传统的基于表面的方法相比，我们的模型捕获了纤维级细节，因此即使在非常近距离观察时也能保持高真实感。 其次，与以前的微外观模型相比，我们的模型是轻量级的，可以实时渲染和编辑。 此外，我们的模型可以有效地进行预过滤，从而产生多尺度表示，可以在不同的分辨率下进行渲染，而无需大量的超采样（ super-sampling）。

从技术上讲，我们的贡献包括：

* 我们提出了一种新的多尺度微观外观模型来描述薄织物的纤维级几何和光学特性（§4）。 我们的模型涉及混合表示，通过将飞散纤维的薄体积和捕获了常规纤维组成的织物主表面的法线映射高度场相结合来进行表示。
* 我们提出了一种新的模型拟合算法，来将我们的表示拟合到现有的微观外观模型（§5）。 我们还展示了如何对我们的模型进行预过滤以进行多尺度的渲染（第 5.3.5 节）。
* 我们开发了一个端到端的管线，能够在多个尺度上实时渲染我们的混合模型（§6）。



## 2 相关工作

### 基于表面的布料模型（Surface-based cloth models）

几十年来，布料渲染一直是图形领域的一个活跃研究课题，因为布料对许多虚拟场景来说都很重要。 传统上，织物被视为用多边形网格描述的光滑 2D 表面，并且布料与光源之间的交互由基于表面的反射率分布 ^[1][2]^ 捕获。 这些模型不仅轻量级，且产生了高质量的渲染效果。 另一方面，基于表面的模型通常缺乏对在近距离表现出逼真的渲染效果来说至关重要的小尺度细节。 这种级别的保真度和细节对于纺织品设计和虚拟原型制作的应用非常重要。

### 微外观布料模型（Micro-appearance cloth models）

最近一系列的微外观建模技术被开发出来 ^[3][4][7][10][11]^。这些方法将织物的小尺度的几何形状明确描述到了纤维级别，达成了进一步的保真度和细节。然而，由于这些模型的高度复杂性，对它们进行渲染非常具有挑战性。为了解决这个问题，已经开发了几种基于预计算的技术。赵等人 ^[8]^ 引入了一种技术，该技术通过在一小部分基本构建块（basic building blocks）上预先计算光线传输并在运行中有效地组合这些信息来利用大型模型的模块化特性。 Wu 和 Yuksel ^[12]^ 引入了一种基于 GPU 的技术，该技术通过利用“核心纤维”对程序化描述的纤维级别细节的织物进行交互地渲染：将常规纤维束与烘焙的阴影信息和环境遮挡（ ambient occlusion）信息相结合。 Khungurn 等人 ^[9]^ 扩展预计算辐射转移 ^[13]^ 以处理微外观布料模型。通过对单次和多次散射进行解耦，并使用预先计算的能见度和间接辐射信息来近似后者，可以在低精度损失的情况下实现非常好的性能。

不幸的是，这些先前的方法要么缺乏交互式表现 ^[8][9]^，要么缺乏物理精度 ^[12]^，无法做到实时进行预先渲染和编辑微外观布料模型。

### 数据驱动模型（Data-driven models）

布料外观也可以以数据驱动的方式进行建模，例如使用双向纹理函数 (BTF) ^[14]^。 然而，这些表示繁琐且实际上难以操作。 此外，它们的数据通常过于密集，以至于无法捕捉到微观外观模型能够捕捉到的细节水平。

### 纤维散射模型（Fiber scattering models）

我们模型使用的反射率分布受到各种纤维散射模型的启发 ^[4][15][16][17]^。 这些模型利用双向曲线散射分布函数 (BCSDF) 来描述光线如何在单个光纤上发生散射。 这些方法通常包括一些模型，以捕获多次的反射（reflection）和透射（transmission）的光源-纤维的相互作用的结果。 纤维散射模型最初是为渲染头发和绒毛而开发的，被 Khungurn 等人 ^[4]^ 采用以用于布料渲染。

### 模型创建方法（Model creation methods）

在先前的研究中，一些技术已经被开发出来用于使用单个图像作为输入（例如 ^[6][18]^）svn 对织物的编织图案和光学特性进行逆向工程。 这些方法侧重于基于真实照片分析织物属性，并输出传统的基于表面或微观外观的模型。



## 3 背景

我们现在简要回顾一下体积的微外观模型，这些模型将用作我们的模型拟合管线（§5）的输入。

 ### 各向异性的辐射传输（Anisotropic radiative transfer）

Jakob等人 ^[19]^ 引入了对标准辐射传输框架 ^[20]^ 的推广，以更好地处理具有方向变化的结构的各向异性介质。 在此框架下，消亡 $\sigma_t$ 和散射系数 $\sigma_s$ 都与方向相关，相位函数 $f_p$ 采用其一般的 4D 形式（而不是仅取决于传入和传出方向之间的角度）。

### 将织物建模为各向异性介质（Modeling fabrics as anisotropic media）

体积微观外观布料模型将织物描述为各向异性介质。 为了方便地指定所需的辐射传输参数（即  $\sigma_t，\sigma_s$ 和 $f_p$），引入了微薄片模型。 该模型使用其自己的一组随空间变化的参数来确定$\sigma_t，\sigma_s$ 和 $f_p$，包括 (i) 薄片密度（flake density） $\rho$； (ii) 薄片法线的分布（ distribution of flake normals） $D$； (iii) 反照率（albedo） α。

微薄片框架的核心是薄片正态分布 $D$，它与微平面反射模型的正态分布函数 (NDF) 起类似的作用。 在实践中，可以使用许多函数基来指定该分布，包括球谐函数 ^[19]^，高斯函数 ^[3]^ 和 SGGX ^[21]^。 在本文中，我们使用高斯表示（尽管我们的技术不限于这个特定的公式）。 在这种情况下，$D$ 变为具有用户指定平均值 $\omega_f$ 和标准差 $\sigma$ 的球面高斯分布。



## 4 我们的混合模型（Our Hybrid Model）

我们的技术将体积微外观织物模型 ^[3][4][21]^ 作为输入，这些模型将织物的细粒度结构捕获到纤维级别。 与以前通过显式模拟各向异性辐射传输 ^[19]^ 直接渲染这些模型的工作不同，我们将它们转换为混合表示，包括：

* 捕获织物主表面的法线映射高度场，该表面由紧密排列的规则纤维组成，和一个捕获无法使用高度场准确描述的飞散纤维的薄体积（§4.1）；
* 轻量级光照散射模型，表示光源如何与织物的主表面以及飞散的纤维相互作用（§4.2）。

我们的混合模型可以实时渲染，支持设计、零售和娱乐领域的许多应用。 在本节的其余部分，我们将提供有关混合模型描述的更多详细信息。

### 4.1 几何描述（Geometric Description）

现实世界的布纤维通常分为两类：常规纤维和飞散纤维 ^[6][7]^。 常规纤维通常紧密堆积以形成织物的主体。 相比之下，飞散纤维主要在主体之外，对织物的毛绒感外观做出了重大贡献。

基于这种理解，我们的混合模型利用高度场来捕获由紧密排列的规则纤维形成的织物顶部表面和一个薄体积来描述飞散纤维（图 1）。

![Figure 1](E:\Backup Folder\LiHaoyu\github\MyImageBed\Paper-Reading\Rendering\Fabric\Multi-Scale Hybrid Micro-Appearance Modeling\Figure 1.png "图 1")

**图 1：我们的混合模型涉及法线映射高度场和薄体积，分别捕获织物主表面纤维和飞散纤维**

------

不幸的是，渲染细节高度场可能具有挑战性，因为当从远处渲染时它们会导致严重的锯齿。 此外，它们不容易被预过滤，因为这样做会改变模型的固有阴影（intrinsic shadowing）和遮罩结构（ masking structures），导致复杂的整体外观变化，难以修复 ^[22]^。 为了解决这个问题，我们将细节高度场分解为更平滑的版本和法线贴图。 法线贴图与我们的光源散射模型相结合，被进一步预过滤，以实现我们模型的高效多尺度渲染（§ 4.2）。 在实践中，我们对高度图应用低通滤波，以便只保留纱线级结构，而去除纤维级细节。 §7.1 进一步证明了此步骤的有效性。

### 4.2 光源散射模型（Light Scattering Model）

我们技术的另一个主要组成部分是一种新的光散射模型，其灵感来自先前的工作 ^[2][4]^。 在每个表面点 $x$，**假设切线 $t(x)$ 与局部纤维方向对齐**，给定入射和出射方向 $\omega_i,\omega_o$，我们使用由下式给出的 BRDF
$$
f_r(\omega_i,\omega_o)=k_d+F(\eta,\theta_i)cos(φ_i)^\alpha f_{r,s}(\omega_i,\omega_o),\tag{1}
$$
其中 $k_d$ 表示漫反射系数，$F$ 是菲涅耳项，$cos(φ_i)^\alpha$ 捕获阴影效果 ^[2]^，$f_{r,s}$ 是由下式给出的多波瓣镜面反射项（multi-lobe specular term）
$$
f_{r,s}(\omega_i,\omega_o)=\sum_j\frac{k_j}{\sqrt{2\beta\pi}}exp(-\frac{(\theta_i+\theta_o)^2}{2\tilde{\beta}_j^2}),\tag{2}
$$
其中 $j$ 是波瓣索引^1^，并且
$$
\tilde{\beta}_j=exp(-\frac{(\theta_i+\theta_o)^2}{2\gamma_j^2}).\tag{3}
$$
在公式（1）和（2）中，$θ_i$ 和 $θ_o$ 分别是从 $ω_i$ 和 $ω_o$ 到法线平面的角度，$φ_i$ 和 $φ_o$ 由 $ω_i$ 和 $ω_o$ 在法线平面上的投影给出（见 图 2）。

公式（2）描述了镜面反射并涉及许多类似高斯的函数，其中对 $(θ_i+θ_o)$ 的依赖性受到以前用于渲染纤维结构的双向曲线散射分布函数 (BCSDF) 的 R 模式的启发 ^[4][15]^ 。 我们没有引入那些 BCSDF 的高阶模式（例如 TRT），因为我们的模型依赖于漫反射项来捕获多重散射。 我们进一步在 $(φ_i+φ_o)$ 上引入高斯 $\tildeβ_j$ 以更好地处理反射率随 $φ$ 的变化（见 图 6）。

请注意，我们的公式（1）表示的 BRDF 由基础表面 $h$ 和薄体积 $V$ 共享。 对于后者，BRDF 应用于从体积派生的隐式表面（有关详细信息，请参见 §6）。

我们的模型可以进行预过滤，从而产生无需大量超采样即可有效渲染的多尺度表示。 在下一节中，我们将介绍一种新技术，将输入的微外观模型转换为不同尺度的混合表示（§5）。

<img src="E:\Backup Folder\LiHaoyu\github\MyImageBed\Paper-Reading\Rendering\Fabric\Multi-Scale Hybrid Micro-Appearance Modeling\Figure 2.png" alt="Figure 2" title="图 2" style="zoom:80%;" />

**图 2：我们的 BRDF 模型 1 使用的角度定义。**

在这种配置下，角度 $\theta$ 和角度 $φ$ 都在 $-\frac{π}{2}$ 到 $\frac{π}{2}$ 之间变化。 当 $\theta=0$ 时，对应的角度 $\omega$ 位于法线平面内； 当 $φ=0$ 时，$\omega$ 的投影归一化为 $n$。

------











## 参考文献

* [1] P. Irawan and S. Marschner, “Specular reflection from woven cloth,” ACM Trans. Graph., vol. 31, no. 1, pp. 11:1–11:20, 2012.
* [2] I. Sadeghi, O. Bisker, J. De Deken, and H. W. Jensen, “A practical microcylinder appearance model for cloth rendering,” ACM Trans. Graph., vol. 32, no. 2, pp. 14:1–14:12, 2013.
* [3] S. Zhao, W. Jakob, S. Marschner, and K. Bala, “Building volumetric appearance models of fabric using micro CT imaging,” ACM Trans. Graph., vol. 30, no. 4, pp. 44:1–44:10, 2011.
* [4] P. Khungurn, D. Schroeder, S. Zhao, K. Bala, and S. Marschner, “Matching real fabrics with micro-appearance models,” ACM Trans. Graph., vol. 35, no. 1, pp. 1:1–1:26, 2015.
* [5] S. Zhao, W. Jakob, S. Marschner, and K. Bala, “Structure-aware synthesis for predictive woven fabric appearance,” ACM Trans. Graph., vol. 31, no. 4, pp. 75:1–75:10, 2012.
* [6] K. Schroder, A. Zinke, and R. Klein, “Image-based reverse engi- ¨ neering and visual prototyping of woven cloth,” IEEE transactions on visualization and computer graphics, vol. 21, no. 2, pp. 188–200, 2015.
* [7] S. Zhao, F. Luan, and K. Bala, “Fitting procedural yarn models for realistic cloth rendering,” ACM Trans. Graph., vol. 35, no. 4, pp. 51:1–51:11, 2016.
* [8]  S. Zhao, M. Hasan, R. Ramamoorthi, and K. Bala, “Modular ˇ flux transfer: Efficient rendering of high-resolution volumes with repeated structures,” ACM Trans. Graph., vol. 32, no. 4, pp. 131:1– 131:12, 2013.
* [9] P. Khungurn, R. Wu, J. Noeckel, S. Marschner, and K. Bala, “Fast rendering of fabric micro-appearance models under directional and spherical gaussian lights,” ACM Trans. Graph., vol. 36, no. 6, pp. 232:1–232:15, 2017.
* [10] K. Schroder, R. Klein, and A. Zinke, “A volumetric approach to predictive rendering of fabrics,” in Computer Graphics Forum, vol. 30, no. 4, 2011, pp. 1277–1286.
* [11] G. Loubet and F. Neyret, “A new microflake model with microscopic self-shadowing for accurate volume downsampling,” in Computer Graphics Forum, vol. 37, no. 2, 2018, pp. 111–121.
* [12] K. Wu and C. Yuksel, “Real-time cloth rendering with fiber-level detail,” IEEE transactions on visualization and computer graphics, vol. 25, no. 2, pp. 1297–1308, 2017.
* [13] P.-P. Sloan, J. Kautz, and J. Snyder, “Precomputed radiance transfer for real-time rendering in dynamic, low-frequency lighting environments,” ACM Trans. Graph., vol. 21, no. 3, pp. 527–536, 2002.
* [14] K. J. Dana, B. van Ginneken, S. K. Nayar, and J. J. Koenderink, “Reflectance and texture of real-world surfaces,” ACM Trans. Graph., vol. 18, no. 1, pp. 1–34, 1999.
* [15] S. R. Marschner, H. W. Jensen, M. Cammarano, S. Worley, and P. Hanrahan, “Light scattering from human hair fibers,” ACM Trans. Graph., vol. 22, no. 3, pp. 780–791, 2003.
* [16] A. Zinke and A. Weber, “Light scattering from filaments,” IEEE Transactions on Visualization and Computer Graphics, vol. 13, no. 2, pp. 342–356, 2007.
* [17] C. Aliaga, C. Castillo, D. Gutierrez, M. A. Otaduy, J. LopezMoreno, and A. Jarabo, “An appearance model for textile fibers,” in Computer Graphics Forum, vol. 36, no. 4, 2017, pp. 35–45.
* [18] G. C. Guarnera, P. Hall, A. Chesnais, and M. Glencross, “Woven fabric model creation from a single image,” ACM Transactions on Graphics (TOG), vol. 36, no. 5, p. 165, 2017.
* [19] W. Jakob, A. Arbree, J. T. Moon, K. Bala, and S. Marschner, “A radiative transfer framework for rendering materials with anisotropic structure,” ACM Trans. Graph., vol. 29, no. 4, pp. 53:1– 53:13, 2010.
* [20] S. Chandrasekhar, Radiative transfer. Courier Corporation, 1960.
* [21] E. Heitz, J. Dupuy, C. Crassin, and C. Dachsbacher, “The sggx microflake distribution,” ACM Trans. Graph., vol. 34, no. 4, pp. 48:1–48:11, 2015.
* [22] S. Zhao, L. Wu, F. Durand, and R. Ramamoorthi, “Downsampling scattering parameters for rendering anisotropic media,” ACM Trans. Graph., vol. 35, no. 6, pp. 166:1–166:11, 2016.
* [23] F. Luan, S. Zhao, and K. Bala, “Fiber-level on-the-fly procedural textiles,” Comput. Graph. Forum, vol. 36, no. 4, pp. 123–135, 2017.
* [24] T. J. Kang, C. H. Kim, and K. W. Oh, “Automatic recognition of fabric weave patterns by digital image analysis,” Textile Research Journal, vol. 69, no. 2, pp. 77–83, 1999.
* [25] J. C. Lagarias, J. A. Reeds, M. H. Wright, and P. E. Wright, “Convergence properties of the nelder–mead simplex method in low dimensions,” SIAM Journal on optimization, vol. 9, no. 1, pp. 112–147, 1998.
* [26] N. Tatarchuk, “Practical parallax occlusion mapping with approximate soft shadows for detailed surface rendering,” in ACM SIGGRAPH 2006 Courses, 2006, pp. 81–112.
* [27] J. Wang, P. Ren, M. Gong, J. Snyder, and B. Guo, “All-frequency rendering of dynamic, spatially-varying reflectance,” ACM Trans. Graph., vol. 28, no. 5, pp. 133:1–133:10, 2009.
* [28] K. Xu, W.-L. Sun, Z. Dong, D.-Y. Zhao, R.-D. Wu, and S.-M. Hu, “Anisotropic spherical gaussians,” ACM Trans. Graph., vol. 32, no. 6, pp. 209:1–209:11, 2013.

