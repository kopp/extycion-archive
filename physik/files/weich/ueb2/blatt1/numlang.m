% Simuliert Langevingl numerisch
% Liefert Trajektorien und VACF 

% Michael Kopp

% 1.
% DGL:   v' + v = f
% Euler: v(n+1) = ( f(n) - v(n) ) Delta_t + v(n)
%               = f(n) Delta_t + ( 1 - Delta_t ) v(n)
% 
% 2.
% DGL: v = f
%
% Fuer Ort: x(t+1) = x(t) + v(t) Delta_t

% Gibt schoene Bildchen als eps aus
% kor_lang.eps  kor_ueber.eps  traj.eps

% Einheiten:
% Zeit: t_0 = m/\gamma
% Geschw. kT = mv_0^2/2 --> v_0 = \sqrt( 2kT/m )
% Kraft: F_0 = mv_0/t_0 = \gamma \sqrt( 2kT/m )


%% Parameter
% Anz. Zeitschritte
N = 10000
% Zeitschritt
dt = 0.001 
% Anz. Ensemble
M = 100 

% Zufallszahlen erzeugen
rn = randn( N , M ) ;

% leerer Vekt. fuer Geschw. (v(0,:) ist Anfangsgeschw.)
v = zeros( N + 1, M ) ;

% Zeitschleife -- Geschwindigkeiten
for ii = [1:N]
	v(ii+1,:) = dt * rn(ii,:)  + ( 1 - dt ) * v(ii,:) ;
end


%% Autokorrelationen
N0 = N/2 ; % verw. diesen Schritt als ersten.
dt_list = [1:N] ;
cor_list1 = zeros( size( dt_list ) ) ;
cor_list2 = zeros( size( dt_list ) ) ;
for ii = [ 1: length( dt_list ) ] 
	cor_list1(ii) = mean( v(N0,:) .*  v(dt_list(ii),:) ) ;
	cor_list2(ii) = mean( v(N0,:) .* rn(dt_list(ii),:) ) ;
end


%% Ort

% Ort (nach DGL 1 bzw 2)
x1 = zeros( N+1 , M ) ;
x2 = zeros( N+1 , M ) ;

% Integration fuer x
for ii = [1:N]
	x1(ii+1,:) = x1(ii,:) + dt * v(ii,:) ;
	x2(ii+1,:) = x2(ii,:) + dt * rn(ii,:) ;
end


%% Ausgabe
% Trajektorien
plot( ...
[1:N+1]/dt , x1(:,1) , ";Langevin;"...
, [1:N+1]/dt , x1(:,2) , ";Langevin;" ...
, [1:N+1]/dt , x2(:,3) , ";ueberdaempft;"...
, [1:N+1]/dt , x2(:,4) , ";ueberdaempft;"...
)
xlabel( "Zeit" );
ylabel( "Ort" );
title( "Trajektorien -- Beispiele" );
print( "traj.eps" , "-deps" , "-color" );

pause

% Autokorrelationen
% ACF sollte Deltafkt sein (Integral = 1)
integral1 = sum( cor_list1 ) % * dt
plot( (dt_list-N0)/dt , cor_list1 ) 
xlabel( "Zeitdifferenz" );
ylabel( "Geschwindigkeitsautokorrelation" );
title( "Geschwindigkeitsautokorrelation: Langevin" );
print( "kor_lang.eps" , "-deps" , "-color" );

pause

integral2 = sum( cor_list2 ) % * dt 
plot( (dt_list-N0)/dt , cor_list2 ) 
title( "Geschwindigkeitsautokorrelation: Ueberdaempft" );
print( "kor_ueber.eps" , "-deps" , "-color" );
