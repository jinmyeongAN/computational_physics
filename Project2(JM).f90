program turnup

real x,y,z,u

read*, x,y

call difference(x,y,z)
call average(x,y,u)
print*,"sum: ",summation(x,y),"difference: ",z,"average ",u

stop
end 

function summation(a,b)
summation=a+b
return
end

subroutine difference(a,b,dif)
if(a>b) then
	dif=a-b
elseif(a==b) then
	dif=0
else
	dif=b-a
endif
return
end

subroutine average(a,b,aver)
aver=(a+b)/2
return
end


