@echo off
for %%f in (*.ppm) do python3 convert.py "%%f" ppm jpeg