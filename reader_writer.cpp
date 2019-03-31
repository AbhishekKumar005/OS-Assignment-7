The code for the writer process looks like this:

while(TRUE) 
{
    wait(w);
    
   /* perform the write operation */
   
   signal(w);
}

The code for the reader process looks like this:

while(TRUE) 
{
    //acquire lock
    wait(m);
    read_count++;
    if(read_count == 1)
        wait(w);
    
    //release lock  
    signal(m);  
    
    /* perform the reading operation */
    
    // acquire lock
    wait(m);   
    read_count--;
    if(read_count == 0)
        signal(w);
        
    // release lock
    signal(m);  
} 