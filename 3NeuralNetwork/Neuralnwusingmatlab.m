%%programmer : Manish Sharma
%Date : 30/8/2012
%Time : 1:59 AM

%%
clear all;
clc;

%% different target set generation
load iris_dataset;
irisTargets_d = zeros(4,3,length(irisTargets));

irisTargets_d(1,:,:)=irisTargets; %[ 1 0 0 ; 0 1 0; 0 0 1]'
irisTargets_d(2,:,:)=[irisTargets(:,51:100) irisTargets(:,1:50) irisTargets(:,101:150)]; %[ 0 1 0 ; 1 0 0 ; 0 0 1]'
irisTargets_d(3,:,:)=[irisTargets(:,101:150) irisTargets(:,51:100) irisTargets(:,1:50)]; %[ 0 0 1 ; 0 1 0 ; 1 0 0]'
irisTargets_d(4,:,:)=[irisTargets(:,1:50) irisTargets(:,101:150) irisTargets(:,51:100)]; %[ 1 0 0 ; 0 0 1 ; 0 1 0]'


%% network declaration and training and plot

for i=3:4
    for j=1:4
        Targets=reshape(irisTargets_d(j,:),3,150);
        net = newff(irisInputs,Targets,[i],{'tansig','purelin'});
        [net tr_data]= train(net,irisInputs,Targets);
        result=plotperform(tr_data)
     end
end