x = 0:1:127
y = [0:4:127 127:-4:0 0:4:127 127:-4:0]
z = [0:8:127 127:-8:0 0:8:127 127:-8:0 0:8:127 127:-8:0 0:8:127 127:-8:0]
a = 0.5
f = zeros(128, 128);
i = 0:1/63:1;
for a = 1:1:64
    f(a, :) = (1-i(a))*x + (i(a))*y;
end
for a = 1:1:64
    f(a+64, :) = (1-i(a))*y + (i(a))*z;
end

plot(x, f(80,:))