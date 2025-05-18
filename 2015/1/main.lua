local function get_input_from_file(filename)
	local file = io.open(filename, "r")
	io.input(file)
	return io.read()
end

local function calculate_floor(input)
	if string.len(input) == 0 then
		return 0
	else
		if string.sub(input, 1, 1) == "(" then
			return 1 + calculate_floor(string.sub(input, 2, -1))
		else
			return -1 + calculate_floor(string.sub(input, 2, -1))
		end
	end
end

local input = get_input_from_file(arg[1])
print(calculate_floor(input))
