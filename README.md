#  fc  compile  

   cd   ussuite/fc/build/   
   cmake ..   
   make   
   cp fc/lib/*.a  ../../lib/.   

   chain  chainbase utilities  compile   
   cd ussuite/build  
   cmake ..   
   make  
       
   uoswallet compile   
   cd ussuite  
   cmake .   
   make   
  
 

# uos test tool set

check openssl is or   not  support sm2 
openssl ecparam -list_curves | grep SM2
echo -n "abc" | openssl dgst -SM3

