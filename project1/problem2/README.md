# Problem 2

## Design
<h3>One Process</h3>
<p>
For one process we first initialized an array to store all the values from the files.
While parsing through the file the max and average were calculated.
Then we went through and found the hidden keys.
</p>
<h3>One Process</h3>
<p>
For multiple process we initialized the array of number the same as with one process. 
We also computed the max and average while populating again. 
Then essentially we had the parent create a child and then we had that child create a child.
Then that granchild would have a child and so on.
Each child was responsible for parsing through a given chuunck of the array.
The number of total process we had was H processes. 
So each rpocess found one key.
</p>

## Running 

```bash
    make
    ./main <L> <H> <filename> <mode>
```
```txt
    mode = 1 : use one process
    mode = 2 : use multiple process
```

## Example One Process

```bash
    make
    ./main 100 15 test100.txt 1
```

output
```bash
    Max = 99, Average = 31.600000
    Hi I am process 67047 and I found a hidden key at A[4]
    Hi I am process 67047 and I found a hidden key at A[9]
    Hi I am process 67047 and I found a hidden key at A[14]
    Hi I am process 67047 and I found a hidden key at A[19]
    Hi I am process 67047 and I found a hidden key at A[24]
    Hi I am process 67047 and I found a hidden key at A[29]
    Hi I am process 67047 and I found a hidden key at A[34]
    Hi I am process 67047 and I found a hidden key at A[39]
    Hi I am process 67047 and I found a hidden key at A[44]
    Hi I am process 67047 and I found a hidden key at A[49]
    Hi I am process 67047 and I found a hidden key at A[54]
    Hi I am process 67047 and I found a hidden key at A[59]
    Hi I am process 67047 and I found a hidden key at A[64]
    Hi I am process 67047 and I found a hidden key at A[69]
    Hi I am process 67047 and I found a hidden key at A[74]
```

## Example Process Tree

```bash
    make
    ./main 100 15 test100.txt 2
```

output
```bash
    Max = 99, Average = 31.600000
    I am process 67063 and I found the key at 4
    I am process 67064, my parent is 67063
    I am process 67064 and I found the key at 9
    I am process 67065, my parent is 67064
    I am process 67065 and I found the key at 14
    I am process 67066, my parent is 67065
    I am process 67066 and I found the key at 19
    I am process 67067, my parent is 67066
    I am process 67067 and I found the key at 24
    I am process 67067 and I found the key at 29
    I am process 67068, my parent is 67067
    I am process 67068 and I found the key at 34
    I am process 67069, my parent is 67068
    I am process 67070, my parent is 67069
    I am process 67069 and I found the key at 39
    I am process 67070 and I found the key at 44
    I am process 67071, my parent is 67070
    I am process 67071 and I found the key at 49
    I am process 67072, my parent is 67071
    I am process 67072 and I found the key at 54
    I am process 67072 and I found the key at 59
    I am process 67073, my parent is 67072
    I am process 67074, my parent is 67073
    I am process 67073 and I found the key at 64
    I am process 67074 and I found the key at 69
    I am process 67075, my parent is 67074
    I am process 67075 and I found the key at 74
    I am process 67076, my parent is 67075
    I am process 67076 and I found the key at 79
    I am process 67077, my parent is 67076
    I am process 67077 and I found the key at 84
    I am process 67077 and I found the key at 89
    I am process 67078, my parent is 67077
```

