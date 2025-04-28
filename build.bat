@echo on 

setlocal EnableDelayedExpansion

SET filesForCompilation=
FOR /R %%f in (src\*.cpp) do (
    set filesForCompilation=!filesForCompilation! %%f
)
echo %filesForCompilation%
set compiler_flags=-MTd -Od -Oi -Gm- -GR- -EHsc -W4 -WX -wd4244 -wd4100 -wd4702 -fp:fast -std:c++20 -FC -FS -Z7 -D_UNICODE -DUNICODE
set linker_flags=-opt:ref kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib winspool.lib comdlg32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  
set debug_build_flags=/DEBUG /PDB:"Chili_Direct3d.pdb" /SUBSYSTEM:WINDOWS /MACHINE:X64 
set out_file=/OUT:"Chili_Direct3d.exe"
IF NOT EXIST Build mkdir Build
IF NOT EXIST Build\Debug mkdir Build\Debug
pushd Build\Debug

cl.exe %compiler_flags% %filesForCompilation% /link %out_file% %linker_flags% %debug_build_flags% 

DEL *.obj 
popd
