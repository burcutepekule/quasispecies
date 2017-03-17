clear all;close all;clc;
set(0,'DefaultAxesFontSize', 16)
set(0,'DefaultTextFontSize', 16)
load('quasi_data')
fflat   = 0.25;
muc     = 1-fflat;
muc_bit = 1-((1-muc)^(1/16));
masterSeq = reshape(mean(masterSeq,1),size(masterSeq,2),size(masterSeq,3));
cmap=[255,128,189;
221,127,182;
185,127,176;
150,126,170;
120,125,165;
103,125,162;
87,124,159;
71,124,156;
70,136,156;
85,162,159;
100,188,161;
115,213,164;
129,227,172;
142,236,182;
156,246,192;
169,255,202]./255;
screensize = get(0,'ScreenSize');
sz    = [400 700];
xpos  = ceil((screensize(3)-sz(2))/2);
ypos  = ceil((screensize(4)-sz(1))/2);
h=figure('Position', [xpos , ypos, sz(2), sz(1)]);
p0=semilogy(muVec,(masterSeq(:,1)),'linewidth',2,'color',[0 0 0]);
hold on;
leg{1} = ['d = ' num2str(0)];

for l=2:hammingDists(end)
    p{l}=semilogy(muVec,(masterSeq(:,l)),'linewidth',2,'color',cmap(l-1,:));
    leg{l} = ['d = ' num2str(l)];
end
semilogy([muc_bit muc_bit],[10^-1 10^2],':','linewidth',2,'color',[0.3 0.3 0.3]);
grid on;
axis([0 0.15 10^-1 10^2])
xlabel('Mutation rate per bit $\mu_b$','interpreter','latex')
ylabel('Number of strings')
legend(leg,'location','northeastoutside')
