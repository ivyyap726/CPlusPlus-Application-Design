# Module 12 - C++ & AI

**AI system I researched:** PyTorch, one of the most popular machine learning libraries. Even though most people write PyTorch code in Python, the core of PyTorch (called ATen, part of a library called libtorch) is actually written in C++. ([Understanding ATen: PyTorch's tensor library](https://developers.redhat.com/articles/2026/02/19/understanding-aten-pytorchs-tensor-library), [LibTorch: The C++ Powerhouse Driving PyTorch](https://medium.com/@pouyahallaj/libtorch-the-c-powerhouse-driving-pytorch-ee0d4f7b8743))

**What C++ contributes:** Python is easy to write and great for experimenting, but it is much slower at actually doing the math (the tensor operations) that a machine learning model needs millions of times per second. PyTorch uses C++ underneath for that heavy lifting because C++ gives direct control over memory and runs much closer to the hardware, so the real number-crunching is fast even though the model is written in simple Python code on top.

**Performance feature I added:** My Budget Tracker already had a `binarySearchByID()` function from Module 7. For this module I added a "Run Performance Benchmark" option (Main Menu choice 6) that builds a synthetic list of 100,000 record IDs and times how long it takes to find one with a plain linear search versus `binarySearchByID()`.

Example result from running it:
```
----- Performance Benchmark (100000 records) -----
Searching for the last ID, the worst case for linear search.
Linear search:  found at index 99999 in 207.477 microseconds.
Binary search:  found at index 99999 in 0.242 microseconds.
Binary search is the same algorithm already used by Search Record and Delete Record.
------------------------------------------------
```

Binary search found the record roughly 800 times faster than linear search. My app only has 10 records right now, so the difference does not matter yet, but this is exactly the kind of thing that matters a lot in a real system like PyTorch: when the data gets huge, the only way to stay fast is to use C++ and a smart algorithm, not just more code written in an easier language.
