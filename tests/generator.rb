#!/usr/bin/ruby

SIGN = [-1, 1]

# ----- Sum Tests ----- 
1.upto(5) do |id|
    file_name = "test_sum_#{id}.txt"
    test_file = File.new(file_name, "w")
    digits = rand(200) + 1
    a = rand(10**digits) * SIGN[rand(2)]

    digits = rand(200) + 1
    b = rand(10**digits) * SIGN[rand(2)]

    c = a + b

    test_file << a << "\n" << b << "\n" << c
    test_file.close
end

# ----- Subtract Tests ----- 
1.upto(5) do |id|
    file_name = "test_subtract_#{id}.txt"
    test_file = File.new(file_name, "w")
    digits = rand(200) + 1
    a = rand(10**digits) * SIGN[rand(2)]

    digits = rand(200) + 1
    b = rand(10**digits) * SIGN[rand(2)]

    c = a - b

    test_file << a << "\n" << b << "\n" << c
    test_file.close
end


# ----- Multiply Tests ----- 
1.upto(5) do |id|
    file_name = "test_mult_#{id}.txt"
    test_file = File.new(file_name, "w")
    digits = rand(500) + 1
    a = rand(10**digits) * SIGN[rand(2)]

    digits = rand(500) + 1
    b = rand(10**digits) * SIGN[rand(2)]

    c = a * b

    test_file << a << "\n" << b << "\n" << c
    test_file.close
end

# ----- Division Tests ----- 
1.upto(5) do |id|
    file_name = "test_div_#{id}.txt"
    test_file = File.new(file_name, "w")
    digits = rand(500) + 1
    a = rand(10**digits) * SIGN[rand(2)]

    digits = rand(500) + 1
    b = (rand(10**digits) + 1) * SIGN[rand(2)]

    # Avoid rounding to -Inf (i.e 5 / 2 = 2 and -5 / 2 = -3)
    c = a / b
    if a < 0 and b > 0
        c = -(-a / b)
    end

    if b < 0 and a >= 0
        c = -(a / -b)
    end

    test_file << a << "\n" << b << "\n" << c
    test_file.close
end


# ----- Modulo Tests ----- 
1.upto(5) do |id|
    file_name = "test_mod_#{id}.txt"
    test_file = File.new(file_name, "w")
    digits = rand(100) + 1
    a = rand(10**digits)

    digits = rand(10) + 1
    b = (rand(10**digits) + 1)

    c = a % b
    test_file << a << "\n" << b << "\n" << c
    test_file.close
end

