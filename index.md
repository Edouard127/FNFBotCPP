
### OPENCV CUDA 10 ARCH BIN >3.0 (aka pre-build) IS [HERE](https://mega.nz/file/TipGURQT#aeWBPcYdLQtbP1Llnw7Mq8RWuniDVddKZM1PDlWca8Y)

### Welcome to the project of FNFBot

## _This project have been forked from [vantonuk35/Fnf_bot](https://github.com/vantonuk35/Fnf_bot)_

In this page we are going to show you how to compile the code.



### **THIS IS FOR BUILD ONLY**
### **If you want the executable, go there** [Download](https://github.com/Edouard127/Fnf_bot/releases)

Step 1: Download the pre-built library [Download](https://github.com/opencv/opencv/releases/download/4.5.3/opencv-4.5.3-vc14_vc15.exe)

Run the downloaded .exe file to extract the archive.

For the sake of uniformity, this tutorial will assume that you’ve extracted the contents to C:\

Download and install the Microsoft DirectX Developpement Kit from the website [Download](https://www.microsoft.com/en-us/download/confirmation.aspx?id=6812)

Step 2: Add to path

Add opencv’s bin directory to path.


![Path](https://miro.medium.com/max/812/1*YWVN2dZry40-U9LO_VrpYg.png)

Step 3: Create a project in Visual Studio 2019

In this step, we’re creating a new project in Visual Studio 2019. Note that the settings we set below are only applied to the new project. 
If you create a new project, you’ll need to repeat the steps below.

![](https://miro.medium.com/max/1400/1*hxz73y6uMvC-EPCnMjqKWA.png)

![](https://miro.medium.com/max/1400/1*Fgw0Rfa47_PJN5AS4aJU-Q.png)

Before we go any further, I want to outline the steps we’re taking and why we are performing each step.

Set platform target to x64 — Pre-built binaries are built for x64 Windows platforms.

Add to Include Directories —Tell the compiler how the OpenCV library looks. This is done by providing a path to the header files (build/include).

Add to Library Directories — Tell the linker where it can find the lib files for different modules.

Add Additional Dependencies — List .lib files for different modules. Note that we’re only going to list a single all-in-one file named opencv_world.

Make sure to also add the DirectX Dev Kit includes and libs directory

![](https://miro.medium.com/max/700/1*9E3Ey4WaZdVyMeGGKlF4yw.png)

![](https://miro.medium.com/max/422/1*Iuwu90ILhOvm1vIg0qOpWg.png)

![](https://miro.medium.com/max/700/1*BXuZ209nCCTTmUGNUaJVyw.png)

![](https://miro.medium.com/max/422/1*Omrvea2MGyY-9Ll2N3OGCQ.png)

The VC++ Directories tab should look like below:

![](https://miro.medium.com/max/700/1*u1mu1Dfl8xdd6-EzgY8HKg.png)

It’s time to list the module dependencies. We are only going to add a single all-in-one module named "opencv_world452.lib" and "opencv_world452d.lib"

We now should be ready.



### Support or Contact

Having trouble ? 
## Discord: 
Kamigen^2#1087 (Who writted this)

Vadim Antonuk#7941 (The original creator)


If in any case you cannot add both of us, you can check our current username on [discord.id](https://discord.id)

Kamigen^2#1087: 381916855365009418

Vadim Antonuk#7941: 439112278613426187

__
### Requirement
## Minimum

Minimum requirement:

Windows =< 7

RAM =< 4GB

CPU Duo Cores 2.7 GHz

## Recommended

Recommended:

Windows 10

RAM =< 4GB

CPU Quad Cores 3.5GHz
 


Example gameplay of **STRESS TEST**
<video width="320" height="240" controls>
  <source type="video/mp4" src="https://cdn.discordapp.com/attachments/811283553114390528/863195122585305098/8mb.video-iJO-Mb93XZv5.mp4">
</video>

Example of real gameplay

<video width="320" height="240" controls>
  <source type="video/mp4" src="https://cdn.discordapp.com/attachments/754151007612567575/863042859267522590/2021-07-09_08-50-27.mp4">
</video>


