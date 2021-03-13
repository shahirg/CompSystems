# Problem3

## Running
```bash
    make
    ./main
```

## Output

```bash
    Started Process A, pid=1512
    Process A, pid=1512: Forked B, pid=1513
    Started Process B, pid=1513
    Process A, pid=1512: Forked C, pid=1514
    Process A, pid=1512: Waiting for children termination
    Process B, pid=1513: Forked D, pid=1515
    Process B, pid=1513: Waiting for children termination
    Started Process C, pid=1514
    Process C, pid=1514: Waiting for children termination
    Started Process D, pid=1515
    Process D, pid=1515: Waiting for children termination
    Process C, pid=1514: Ending process
    Process D, pid=1515: Ending process
    Process B, pid=1513: Child allowing its own terminating with status 10
    Process B, pid=1513: Ending process
    Process A, pid=1512: Child allowing its own terminating with status 4
    Process A, pid=1512: Child allowing its own terminating with status 6
    Process A, pid=1512: Ending process
```