# File structrue of executable `v1.0`

This document introduces the whole file structure of the executable, which is used for the virtual machine.

## Introduction

Each executable contains five elements: statements of processors, which contain code segments(treated as automata), mutices, instance of processors, their data dependencies and executing orders. Since elements are necessary in all occasions, there is no header in current version, and they are in a fixed order. All information were piled up by assembler and loaded by the VM as one single file.

## Structure

The details of file structure in order.

#### Processor Statements

There is a 32bit-integer at the start, means that how many statements current file have, assumes the value is N. It follows N statementes of processors, each starts with a statement header, which contains essential configurations of the processor, like the stack, size of different code and data segments. After that is a raw code segment. In the end is data initializer that contains several offset positions and its data type and raw values. If any of intry these is zero, then the number of current elements are stored as a zero, and the VM will skip reading this at the loading stage.

#### Mutices

It has been mentioed before that a mutex in this scenario only includes the  

#### Processor Instances

#### Data Dependencies

#### Executing Orders
