load ft.txt
load fm.txt
i = ft(:,1);
r1= ft(:,2);
r2 = ft(:,3);
r3 = ft(:,4);
r4 = ft (:,5);
plot(i,r1,'-*')
hold on
plot(i,r2,'-*')
hold on 
plot(i,r3,'-*')
hold on 
plot(i,r4,'-*')
legend("before-presmoothing","after pre-smoothing","after coarse-correction","after post-smoothing")
title("Residual evolution for 2-grid algorithm with SGS-smoother on a 1281x1281 grid")
ylabel("||r||/||b||")
xlabel("# itteration")

