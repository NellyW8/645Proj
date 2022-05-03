# 645Proj
## Team members:
    
    - Yiting Wang
    - Yashi Sinha

## Deliverable List:

1. Human readable IR produced by our pass:
    
    1). `example1.hello.ll`

    2). `example2.hello.ll`

    3). `example3.hello.ll`

    4). `example4.hello.ll`

2. Source code:
    
    `Hello.cpp`

4. To remove dead arguments from functions. We used the `deadargelim` pass separately on the command line.

opt --deadargelim < input bytecode > -o < output byte code >
