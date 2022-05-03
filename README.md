# 645Proj
## Team members:
    
    - Yiting Wang
    - Yashi Sinha

## Deliverable List:

1. Human readable IR produced from our program is in the [ProgramOutputs](https://github.com/NellyW8/645Proj/tree/main/ProgramOutputs) folder:
    
    1). [example.1hello.ll](https://github.com/NellyW8/645Proj/tree/main/ProgramOutputs/example.1hello.ll)

    2). [example.2hello.ll](https://github.com/NellyW8/645Proj/tree/main/ProgramOutputs/example.2hello.ll)

    3). [example.3hello.ll](https://github.com/NellyW8/645Proj/tree/main/ProgramOutputs/example.3hello.ll)

    4). [example.4hello.ll](https://github.com/NellyW8/645Proj/tree/main/ProgramOutputs/example.4hello.ll)

2. Source code:
    
    [Hello.cpp](https://github.com/NellyW8/645Proj/tree/main/Hello.cpp)
3. Test cases and original human readable IR is in the [TestOutputs](https://github.com/NellyW8/645Proj/tree/main/TestOutputs) folder:

4. To remove dead arguments from functions. We used the `deadargelim` pass separately on the command line.

opt --deadargelim < input bytecode > -o < output byte code >

5. To run our program, please check [runfile.txt](https://github.com/NellyW8/645Proj/tree/main/runfile.txt) and follow the instructions.
