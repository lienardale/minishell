echo "--- HARDCORE | ---"

rm hardcore_pipe.log hardcore_pipe_errors.log
touch hardcore_pipe.log hardcore_pipe_errors.log
function run(){

}
run 1>> hardcore_pipe.log 2>> hardcore_pipe_errors.log
rm -rf test0