[ -d "./test/" ] && rm -rf ./test/
mkdir test

touch ./test/test.txt

let times=98

for ((i = 0; i <= times*512; i+=512))
do
   echo $i
   ./ssd_fuse_dut /tmp/ssd/ssd_file w 512 $i
   ./ssd_fuse_dut ./test/test.txt w 512 $i
   wait
done

./ssd_fuse_dut /tmp/ssd/ssd_file w 3072 3073
./ssd_fuse_dut /tmp/ssd/ssd_file w 2560 10752
./ssd_fuse_dut /tmp/ssd/ssd_file w 3072 22528
./ssd_fuse_dut /tmp/ssd/ssd_file w 3702 26624
./ssd_fuse_dut /tmp/ssd/ssd_file w 2560 31232
./ssd_fuse_dut /tmp/ssd/ssd_file w 1024 43008
./ssd_fuse_dut /tmp/ssd/ssd_file w 1536 4096
./ssd_fuse_dut /tmp/ssd/ssd_file w 1024 10752
./ssd_fuse_dut /tmp/ssd/ssd_file w 2048 3584


./ssd_fuse_dut ./test/test.txt w 3072 3073
./ssd_fuse_dut ./test/test.txt w 2560 10752
./ssd_fuse_dut ./test/test.txt w 3072 22528
./ssd_fuse_dut ./test/test.txt w 3702 26624
./ssd_fuse_dut ./test/test.txt w 2560 31232
./ssd_fuse_dut ./test/test.txt w 1024 43008
./ssd_fuse_dut ./test/test.txt w 1536 4096
./ssd_fuse_dut ./test/test.txt w 1024 10752
./ssd_fuse_dut ./test/test.txt w 2048 3584

./ssd_fuse_dut /tmp/ssd/ssd_file r 10000 > ./test/ssd_dump.txt
./ssd_fuse_dut ./test/test.txt r 10000 > ./test/test_dump.txt

diff -s ./test/ssd_dump.txt ./test/test_dump.txt
