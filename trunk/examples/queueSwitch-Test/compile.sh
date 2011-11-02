export PROFILERINC='/home/pmistry/perhaad-palantir/trunk/src/libprofiler'
export MISCINC='/home/pmistry/perhaad-palantir/trunk/src/libmisc'
export ADEVICEINC='/home/pmistry/perhaad-palantir/trunk/src/libanalysis-devices'

g++ -o vecadd  matmul.cpp main.cpp -I$PROFILERINC -I$MISCINC -I$ADEVICEINC -I/opt/AMDAPP/include -L/opt/AMDAPP/lib/x86_64 -lOpenCL -L$PROFILERINC -lprofiler -L$MISCINC -lmisc -L$ADEVICEINC -lanalysis-devices -Wall

