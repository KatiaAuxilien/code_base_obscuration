@echo off
for %%f in (*.pgm) do python3 convert.py "%%f" pgm jpeg