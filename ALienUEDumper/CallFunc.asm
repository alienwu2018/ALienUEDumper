EXTERN ComponentCallAddress:qword  

.code
ComponentCall proc uses rcx
    sub rsp,100h
	call qword ptr[ComponentCallAddress]
	add rsp,100h
	ret
ComponentCall endp
end