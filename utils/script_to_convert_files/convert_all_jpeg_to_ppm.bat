@echo off
for %%f in (*.JPEG) do python3 convert.py "%%f" jpeg ppm
