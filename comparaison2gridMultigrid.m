load q3.txt
load mgaccelerated.txt
load mgacceleratedcorrected.txt
load cg.txt

i = q3(:,1);
rtwogrid = q3(:,2);
rmultigrid = q3(:,3);
raccmg = mgaccelerated(:,2);
raccmgc = mgacceleratedcorrected(:,2);
rmgcg = cg(:,2);
plot(i,rtwogrid,'-*');
hold on
plot(i,rmultigrid,'-*');
hold on
plot(i,rmgcg,'-*')
hold on

title("Comparaison of residual evolution between  4 Level multigrid V-cycle and 2-grid" + ...
    "  with SGS-smoother and Vcycle with C-G smoother ")
xlabel("#itterations")
ylabel("||r||/||b||")
legend("two-grid","Vcycle","CG-Vcycle")
figure
plot(i,rmultigrid,'*-')
hold on
plot(i,raccmg,'*-')
hold on
plot(i,raccmgc,'-o')
legend("V-cycle tau = 1", "V-cycle tau","V-cycle tau_corrected")


