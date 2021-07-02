# Win11_no_tpm
A patched (no tpm 2.0 required) windows11 iso maker

***Thanks to Microsoft***, we can't install windows11 on older devices such as Core 2 duo and core i series under 7 generation(*0) ANYMORE

*0 Acroding to Microsoft [you need to have 8 genaration or newer CPU (for intel CPUs)](https://docs.microsoft.com/en-us/windows-hardware/design/minimum/supported/windows-11-supported-intel-processors)

If you try to install windows11 on older devices, you'll see error message like this : 

![win11 need tpm 2.0](https://user-images.githubusercontent.com/45873899/124287446-fa863000-db8a-11eb-8cea-a44461dfe8fa.png)

That's because Microsoft checks if your computer meet minimum requirement.

But, don't worry! **You can bypass it**.

Just install [7zip](https://www.7-zip.org/download.html), [oscdimg](https://go.microsoft.com/fwlink/?linkid=2165884) and download win11_no_tpm.exe from [release]() and follow the instruction.

# How to use

1. Run **win11_no_tpm.exe**
1. Select language
1. The app will check if 7zip is available
    1. If you see '7zip was not found!' message and you've installed 7zip onto a different path, select 7z.exe manually.
    1. If you haven't installed 7zip, install [it](https://www.7-zip.org/download.html)
1. The app will check if oscdimg is available
    1. If you see 'oscdimg was not found!' message and you've installed oscdimg onto a different path, select oscdimg.exe manually.
    1. If you haven't installed oscdimg, install [it](https://go.microsoft.com/fwlink/?linkid=2165884)
1. Select **Windows10.iso**
1. Select **Windows11.iso**
1. The app will make patched windows11.iso (it takes few minutes)
1. **Windows11_no_tpm_2_0.iso** will be generated.
1. Done! You can install Windows11 on any devices.