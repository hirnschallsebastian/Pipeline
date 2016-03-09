# Pipeline
Designed to aid in targeted brute force password cracking attacks.    

Pipeline is built on top of CForce and it's more or less a "simpler" version of Matt Weir's middlechild since you can use it to append all possible combinations of chars.    
Please don't get me wrong... Middlechild is a great tools, but I think it misses some featurs so I created my own tool!    

If you like Pipeline please check out Matt Weir's work over at https://sites.google.com/site/reusablesec/Home/password-cracking-tools/middle-child !    

#### Compile Pipeline
<code>g++ main.cpp -o pipeline -std=c++11 -pthread</code>    

#### Usage

###### Options

    -t <value           Number of threads to use     
    -b <value>          Number of values stored in each thread (Buffer)     
    -w <value>          Uses the specified dictionarys (up to 10)     
    -append             Appends the values to the end of the input word     
    -prepend            Inserts the values to the front of the input word     
    -charSet <value>    Uses a custom charset     
    -max <value>        Specifies how long the inserted string should be (max)
    -min <value>        Specifies how long the inserted string should be at least (min)
    -capFirst           Capitalizes the input word     
    -capAll             Capitalizes the entire word     
    -capLast            Capitalizes the last letter of the input word      
    -capAllButFirst     Capitalizes all the letters but the first one     
    -capAllButLast      Capitalizes all the letters but the last one      
    -capCeption         All cap options one after another      

###### Examples:
<code>
    ./pipeline -w rockyou.txt -w dictionary.txt -capFirst -append -max 3 | ./john -stdin -format=NT hashlist.txt
</code>    
    Takes two input dictionarys, capitalizes the first letter, appends 3 chars and pipes the output to John    


###### How it works

   
Words in your dic.:    

password    
computer    

If you run:    
<code>./pipeline -append -max 3 -capfirst -capnone</code>        
Pipeline will print:    

password    
Password    
computer    
Computer    
password0    
Password0    
computer0    
Computer0    
password1    
Password1    
computer1    
Computer1    

and so on...    

###### Custom Charset

If you want to use a specific charset to append/prepend use -charset    

e.g.    
<code>./pipeline -append -max 3 -capfirst -capnone -charset 2\"\!</code>    

output:    

password    
Password    
computer    
Computer    
password2    
Password2    
computer2    
Computer2    
password"    
Password"    
computer"    
Computer"    

and so on...    
