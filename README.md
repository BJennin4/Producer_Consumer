# Producer_Consumer

This is a workthrough of the producer-consumer problem. 
For use in linux with GCC. 

The producer creates items, or "puts them on a table", and the cosumer consumes them, or "takes them off the table". The max number of items on the table is 2 and the producer will wait when there are 2 items on the table. The consumer will wait when there are 0 items on the table. 

## Compilation
> gcc producer.c -pthread -lrt -o producer
> gcc consumer.c -pthread -lrt -o consumer

## Execution
> ./producer & ./consumer &

## Example Output
