a = 1

function Start()
	return "Lua Start Function Called"
end

function Update()
	a = a+1
	a = a%10
	return "Lua Update Function Called variable a : "..a.."."
end



