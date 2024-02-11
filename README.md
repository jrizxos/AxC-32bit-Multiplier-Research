# AxC-32bit-Multiplier-Research

In this repository we publish the code used to run the Genetic Algorithm experiments for our paper:<br>
**Design space exploration of partial product reduction stage on 32x32 approximate multipliers<br>
Not published yet. Submitted for the 13th International Conference on Modern Circuits and Systems Technologies (MOCAST 2024). (updated: 11/02/2023)

Repository Authors:
- Ioannis Rizos
- Georgios Papatheodorou

**For any questions please create an Issue within this repository.**

---

## Study Results

---

## Requirements

To run our code you need [Python](https://www.python.org/downloads/) installed.
For VHDL synthesis and implementation we use [Cadence Genus](https://www.cadence.com/en_US/home/tools/digital-design-and-signoff/synthesis/genus-synthesis-solution.html), it needs to be installed in your system if you intend to use it.
We tested this program with **Python 3.10.12** and **Cadence Genus 21.10** on **Ubuntu 22.04.2 LTS**.

---

## Setting-up

Clone repository and submodules:
```
> git clone https://github.com/jrizxos/AxC-32bit-Multiplier-Research
> cd AxC-32bit-Multiplier-Research
> git submodule update --init --recursive
```

Install python requirements on your python environment:
```
> pip install -r requirements.txt
```

Generate input for evaluator, Generate library for Genus and compile evaluator:
```
> cd code\ generation\ tools 
> python input_gen.py 
> mv inp.bin ../cppsim
> python libmerge.py
> mv gf180mcu.lib ../tcl_work_dir
> cd ../cppsim 
> make
```

---

## File Structure

```
├── code generation tools            (scripts for automatic generation of code material)
│   ├── axc_wallace_32x32.vhd        (behavioural description of multiplier module, needed by scripts)
│   ├── cpp_gen.py                   (C++ code generator)       
│   ├── findpath.py                  (reverse path finder for AFAs)
│   ├── gf180mcu-pdk                 (gf180mcu-pdk submodule)
│   ├── input_gen.py                 (input generatio script)
│   └── libmerge.py                  (gf180mcu-pdk library merger script)
├── cppsim                           (C++ functional simulator directory)
│   ├── afa.cpp                      (approximate full adder functions)
│   ├── afa.h
│   ├── debug.cpp                    (debug functions)
│   ├── debug.h
│   ├── evaluator.cpp                (MAIN evaluator program)
│   ├── evaluator.h
│   ├── inp.bin                      (inputs file, generated by input_gen.py)
│   ├── Makefile                     (makefile)
│   ├── mul32.cpp                    (32x32 modular multiplier function)
│   ├── mul32.h
│   └── testme.py                    (python-C++ interface test script)
├── highscores.json                  (database for archived individuals, generated by search.py)
├── individual.py                    (individual class)
├── LICENSE                          (liscence file)
├── mins.json                        (minimum values recorded, for use in NSGA-II, and exact multiplier)
├── pareto.json                    	 (search output file, generated by search.py)
├── pareto-final.json                (final pareto for our results)
├── pareto-optimized.json            (optimized pareto for our results)
├── README.md                        (readme file)
├── score_tree.py                    (search tree methods)
├── search.py                        (MAIN search program)
├── tcl_helper.py                    (tcl script helper)
├── tcl_work_dir                     (tcl script working directory)
│   ├── gf180mcu.lib                 (gf180mcu-pdk library, generated by libmerge.py)
│   ├── main_high.tcl                (main tcl script with high effort setting)
│   ├── main_low.tcl                 (main tcl script with low effort setting)
│   ├──vhdl                          (multiplier VHDL code directory)
│   │   ├── axc_wallace.vhd
│   │   ├── ...
│   │   └── out_reg.vhd
│   ├── tcl_out                      (Genus report output directory)
│   └── temp                         (temporary Genus projects directory, safe to delete contents after program finishes)
└── utilities.py                     (utilities to handle the study of produced data)
```
