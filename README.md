# WinBGIDLL Project

In the year 2024 I embarked on the task of reviving the more than 40 old programs from [«The World of Chaos»](https://www.theworldofchaos.com/), released in 2001, which used the old BGI graphics driver, which ran in Turbo C 3.0 of DOS in 16 bits.

So to maintain the magic of programming in the very pure old school style, I decided to continue using the BGI library but modernized to run under Windows, which was precisely the [WinBGI project by Michael Main (University of Colorado)](https://home.cs.colorado.edu/~main/bgi/visual/), who shared the code with the community [on your website](https://winbgim.codecutter.org/).

> The WinBGI project has the advantage that not only does it have a version for Dev-C++, but it also has a version for Visual C++, although updated up to VS2010. This is a great advantage because it could be used with the Visual Studio Community compiler, which has a powerful IDE superior to Dev C++, which is very useful for developing projects in C++, since it has a professional environment to develop academics projects.

Although WinBGI project worked very well to include it as a static library within any project, it seemed like a cumbersome task to apply it to more than 40 programs, I wanted something more copy and paste and more similar to what was done in old school, so I decided to update the project and add a compilation as a DLL.

Additionally, a 64-bit compilation was added, which required some corrections and improvements to be made to the code, so that the library can be used with 64-bit programs. Additionally, missing routines belonging to the old Borland C++/Turbo C conio.h were added.

> #### **I have named this new project WinBGIDLL.**
> In such a way that to add the library it is enough to include WinBGI.dll and the graphics.h header, just as it was done in the old school.

So I updated Michael’s old WinBGI project to be compiled in Visual Studio Community 2017 and also added the projects to create static .lib and dynamic .dll libraries in 32 and 64 bits. Therefore, you can use the old Borland C++ BGI in versions of Visual C++.

> Share with us a comment about your experiences with WinBGIDLL.

> **Get the latest version to start using this graphics library today:**
> ### **[Go to Official website of the WinBGIDLL project](https://www.theworldofchaos.com)**


## For documentation original of the Winbgi library, please see:

- [The WINBGIM Library - Borland BGI Graphics and Mouse For Windows Applications](https://home.cs.colorado.edu/~main/cs1300/doc/bgi/bgi.html)

- [Borland Graphics Interface (BGI) for Windows](https://home.cs.colorado.edu/~main/cs1300/doc/bgi/index.html)