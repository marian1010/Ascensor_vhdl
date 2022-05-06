@ECHO OFF
@REM ###########################################
@REM # Script file to run the flow 
@REM # 
@REM ###########################################
@REM #
@REM # Command line for ngdbuild
@REM #
ngdbuild -p xc3s1000ft256-5 -nt timestamp -bm Practica2.bmm "C:/hlocal/Practica5/implementation/Practica2.ngc" -uc Practica2.ucf Practica2.ngd 

@REM #
@REM # Command line for map
@REM #
map -o Practica2_map.ncd -pr b -ol high -timing -detail Practica2.ngd Practica2.pcf 

@REM #
@REM # Command line for par
@REM #
par -w -ol high Practica2_map.ncd Practica2.ncd Practica2.pcf 

@REM #
@REM # Command line for post_par_trce
@REM #
trce -e 3 -xml Practica2.twx Practica2.ncd Practica2.pcf 

