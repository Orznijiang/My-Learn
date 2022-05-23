# 基于薄织物的多尺度混合微外观建模和实时渲染（Multi-Scale Hybrid Micro-Appearance Modeling and Realtime Rendering of Thin Fabrics）

## 摘要

微外观模型可以为布料渲染提供最先进的渲染质量。 不幸的是，它们通常情况下使用数据密度极大的 3D 或纤维网格来表示，这导致高细节程度的布料模型的渲染成本很高，无法做到实时渲染。 另一方面，传统的基于表面的模型是非常轻量级的，因此渲染速度很快。但是其通常缺乏对设计和原型相关的应用程序来说非常重要的保真度和细节。 这篇文章引入了一种多尺度混合模型来弥补薄织物在基于表面的渲染模型与基于微外观的渲染模型方面的细节差距。 这个多尺度混合模型同时继承了传统的基于表面的模型带来的渲染的快速性和微外观模型带来的丰富细节。 此外，这篇文章提出了一种新算法，将最先进的微外观模型表示转换为一种新的表示，同时定性地保留细节外观，同时通过将这种多尺度混合模型和新的表示方法集成到实时渲染系统中来证明这种技术的有效性。



## 正文

### 1 介绍

布料材质的渲染是高保真渲染中的一个重要部分，它在我们的日常生活中很重要，且经常被运用与计算机图形场景中。此外，准确的布料外观对于纺织品的设计以及制造产业相关的应用来说至关重要。

布料外观的传统建模方法是基于表面的表示方法，例如专门化的BRDF表示^[1][2]^。这些模型通常具有轻量化、渲染速度快的特点，并且能够在远处观察织物时提供一个令人信服的结果，而无法在从近处观察时看到单根的纱线。不幸的是，这些模型缺乏在特写视图中生成逼真结果所需的细粒度细节，而这对于设计和虚拟现实中的许多应用程序来说很重要。

微外观布料模型 ^[3][4][5][6][7]^ 通过将织物的详细结构明确捕获到纤维级别，提供卓越的质量。 这些微观几何形状通常使用高分辨率体积或纤维网格来描述。 由于存在纤维级细节，即使非常仔细地观察，这些模型仍然非常逼真。 与基于表面的模型相比，微外观模型通常是数据密集型且渲染成本高。 即使有大量的预计算，使用这些模型渲染单个图像也可能在 CPU [8] 上花费几分钟，在 GPU [9] 上花费数十秒。









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

