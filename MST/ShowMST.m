function ShowMST(name)

MSTMatrix = dlmread(name);
V = MSTMatrix(1,1);
G2 = zeros(V);

for m = 2:size(MSTMatrix,1)
    x = MSTMatrix(m,1) + 1;
    y = MSTMatrix(m,2) + 1;
    G2(x,y) = MSTMatrix(m,3);
    G2(y,x) = MSTMatrix(m,3);
end

G2 = graph(G2);
plot(G2,'EdgeLabel',G2.Edges.Weight)

end