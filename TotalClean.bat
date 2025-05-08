del /q *.ncb
del /s /q *.ilk
del /s /q *.exe
for /d %%G in ("*") do rmdir /s /q "%%G/Garbage/"

rmdir /s /q "Installer/Debug/"
rmdir /s /q "Installer/Release"

del /s /q BallGame.pdb
