ls -la | < main.c << E < Makefile  cat >> out_file | grep 1 | wc -c | a=5



set follow-fork-mode child



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


