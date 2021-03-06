no_vertices = 32*4*4*2;
Lx = 3;
dx = Lx/no_vertices;

y_array(1:no_vertices) = 0.0;

x_0 = -Lx/2 + dx/2;
for i = 0:(no_vertices-1)
    x_array(i+1) = x_0 + i*dx;
end

plot(x_array, y_array,'.')

fid = fopen('../stokes_plate.vertex','wt');

fprintf(fid,'%d\n', no_vertices);

for i = 1:no_vertices
    fprintf(fid, '%12.7E\t%12.7E\n',x_array(i),y_array(i));
end

fclose(fid);
