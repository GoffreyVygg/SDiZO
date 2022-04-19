function ShowMST(name)

MSTMatrix = dlmread(name);
V = MSTMatrix(1,1);
G = zeros(V);

for m = 2:size(MSTMatrix,1)
    x = MSTMatrix(m,1) + 1;
    y = MSTMatrix(m,2) + 1;
    G(x,y) = MSTMatrix(m,3);
    G(y,x) = MSTMatrix(m,3);
end

G = graph(G);
plot(G,'EdgeLabel',G.Edges.Weight)
title('Liczba wiercholkow:', V)

end