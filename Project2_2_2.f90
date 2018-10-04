program main

real x,y1,y2

read*, x
y1=f1(x)
y2=f2(x)

print*,"N!: ",y1,"N!!: ",y2
stop
end

real function f1(a)
	
	real c,i
	i=1
	c=a
	
	do while(i.lt.a)
		c=c*(a-i)
		i=i+1	
	enddo
	f1=c
	
	return
	end


real function f2(b)
	
	
	real d,i
	i=2
	d=b
	if(b==1) then
		f2=1
	
	else

		do while(i<b)
			d=d*(b-i)
			i=i+2
		enddo
		f2=d

	endif
		
	return
	end
	

