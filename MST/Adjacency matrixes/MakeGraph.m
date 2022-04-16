function graph = MakeGraph(vertex,maxWeight, name)

graph = zeros(vertex,vertex);
start = 2;
for i = 1:vertex
    for j = start:vertex
        graph(i,j) = ceil(rand*maxWeight);
    end
    graph(start:vertex,i) = graph(i,start:vertex);
    start = start + 1;
end
csvwrite(name,graph);

end
