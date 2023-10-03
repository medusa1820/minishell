ls -la | < main.c << E < Makefile  cat >> out_file | grep 1 | wc -c | a=5



====================================================================



set follow-fork-mode child

set follow-fork-mode parent




set follow-exec-mode new

set follow-exec-mode same



====================================================================

                        OPEN PROBLEMS

1. >>, append is not appending LIVE, needs re-opening of out_file

2. 

3. 





====================================================================




first pipe

< in_file0 << E < in_file1 >out_file0 cat >> out_file1 | ls -la







second pipe

ls -la | < in_file0 << E < in_file1 cat >> out_file1 >out_file0

ls -la | < in_file0 << E < in_file1 cat >out_file0 >> out_file1| ls -la

ls -la | < in_file0 cat >> out_file1








third pipe

ls -la | cat > out_file0  | < out_file0 cat >> out_file1

ls -la | grep 3  > out_file0  | < out_file0 cat > out_file1






no pipe

< in_file0 cat > out_file1





========================== TESTING EXIT CODE =====================




bash-3.2$ ls -la | grep 45
bash-3.2$ echo $?
1
bash-3.2$ 







bash-3.2$ ls | cab | cat
bash: cab: command not found
bash-3.2$ echo $?
0
bash-3.2$ 







