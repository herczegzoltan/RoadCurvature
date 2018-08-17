
fid = fopen('output_coord.txt'); %from task 1.
tline = fgetl(fid);
while ischar(tline)
    C = strsplit(tline,';');
    x = C(1);
    y = C(2);
   
    X_val = str2double(x);
    Y_val = str2double(y);


    plot(X_val,Y_val,'r*','markers',12)
    tline = fgetl(fid);
    disp("x:"+x +"y:"+ y);
    hold on


end

xlabel('X') 
ylabel('Y')



fid = fopen('results.txt'); %from task 2.
tline = fgetl(fid);

while ischar(tline)
    C = strsplit(tline,';');
    Adata = C(1);
    Bdata = C(2);
    Cdata = C(3);
   
    Aval = str2double(Adata);
    Bval = str2double(Bdata);
    Cval = str2double(Cdata);
    
    tline = fgetl(fid);

    disp("a:"+Aval +" b:"+ Bval +" c:" + Cval );
    
    fplot(@(x)Aval.*x.^2 + Bval.*x + Cval)


    
end
hold off

fclose(fid);




