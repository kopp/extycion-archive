% simuliert bewegung eines teilchens in molekularer ratsche
%
% Langevingleichung:   v' + v = f + K
% mit Zufallskraft f und Potential-Kraft K = - \del_x V
% 
% Fuer Ort: x(t+1) = x(t) + v(t) Delta_t
%
% Einheiten:
% Zeit: t_0 = m/\gamma
% Geschw. kT = mv_0^2/2 --> v_0 = \sqrt( 2kT/m )
% Kraft: F_0 = mv_0/t_0 = \gamma \sqrt( 2kT/m )


isscript_ = 1 ;

tic


%% konstanten
% als globale deklarieren
global M anteil anisotropie dt periodizitaet intensitaet
% zeitschritte (anzahl)
N = 30000
% ensemble
M = 300
% anteil pot. eingeschaltet
anteil = 0.2  %0.2
% anisotropie (laengenanteil erchts schraeg)
%   laengenperiodizitaet ist immer 1
anisotropie = 0.8
% zeitschritt
dt = 0.01
% periodizitaet mit der potential umschaltet (zeit)
% periodizitaet = 60 %10
periodizitaet = str2double( (argv()){1} ) % pass as argv1
% intensitaet des Potentials
intensitaet =  2 % RatchetStudent: ca. 5

% art der Dynamik
% 1 gedaempft
% 2 ueberdampft
art_der_dynamik = 1

maximale_zeit = N*dt




%% funktionen
% potential
function y = potential(x,t)
	global M anteil anisotropie dt periodizitaet intensitaet
	y = zeros( size( x ) ) ;
	if( mod( t , periodizitaet ) > anteil*periodizitaet )
		% potential ist aus
		return ;
	end
	% wenn nicht: berechne potential

	% reduziere koordinaten 
	x = mod(x,1) - (1-anisotropie) ;
	% reduzierte x-werte sind zwischen [1-anisotropie:anisotropie]
	% --> potentialmin ist hier bei 0

	steigung_links = - intensitaet/(1-anisotropie) ;
	steigung_rechts = intensitaet/anisotropie ;

	y = x.*steigung_links.*(x<0) + x.*steigung_rechts.*(x>=0) ;
end

% kraft
% wie potential, nur das nur die steigungen uebergeben werden
function y = kraft(x,t)
	global M anteil anisotropie dt periodizitaet intensitaet
	y = zeros( size( x ) ) ;
	if( mod( t , periodizitaet ) > anteil*periodizitaet )
		% potential ist aus
		return ;
	end
	% wenn nicht: berechne potential

	% reduziere koordinaten 
	x = mod(x,1) - (1-anisotropie) ;
	% reduzierte x-werte sind zwischen [1-anisotropie:anisotropie]
	% --> potentialmin ist hier bei 0

	steigung_links = - intensitaet/(1-anisotropie) ;
	steigung_rechts = intensitaet/anisotropie ;

	y = -steigung_links.*(x<0) -steigung_rechts.*(x>=0) ;
end


%% variablen
% pos (ein ensemble ist ein spaltenvektor)
x = zeros( M , N ) ;
% geschw.
v = zeros( M , N ) ;
% zeit
t_list = [0:dt:(N-1)*dt] ;



%% loop
for ii = [ 1:N-1 ]
	% langevingleichung
	% vgl blatt01
	switch( art_der_dynamik )
	case { "gedaempft" 1 }
		% gedaempft -- ma noch entscheidend
		v(:,ii+1) = (1-dt) * v(:,ii) + dt .* ( randn(M,1) + kraft( x(:,ii) , dt*ii ) - v(:,ii) ) ;
		% euler integrator
		x(:,ii+1) = x(:,ii) + dt .* v(:,ii) ;
	case { "ueberdaempft" 2 }
		% ueberdaempft
		x(:,ii+1) = x(:,ii) + dt .* ( randn(M,1) + kraft( x(:,ii) , dt*ii ) - v(:,ii) ) ;
	otherwise
		error( "select `gedaempft' or `ueberdaempft' for art_der_dynamik" );
	end
end



%% bilde mittel
% ,1 -> ensemblemittel
x_mean = mean( x , 1 );
v_mean = mean( v , 1 );

% fuer lineare x_mean:
% v_mittel = mean( x_mean( [ N/10 : N ] ) ./ t_list( [N/10 : N] )  ) 
polynom_koeffizienten = polyfit( t_list , x_mean , 1 ) ;
v_mittel = polynom_koeffizienten( 1 )

%% output
% plot x
plot( t_list , x_mean , t_list , polyval( polynom_koeffizienten , t_list ) ) ;
% save x
out_data = [ t_list'  x_mean' ] ;
out_name = sprintf( "x_mean_%04d_%04d_%04d_%d" , M , anisotropie*100 , periodizitaet , art_der_dynamik ) ; 
save( "-ascii" , out_name , "out_data" ) ;
% % save potential
% interesting_x_range = [ min( x_mean ) : (max(x_mean)-min(x_mean))./1000 : max( x_mean ) ] ' ;
% out_potential = [ interesting_x_range potential( interesting_x_range , 0 ) ] ;
% out_name_potential = strcat( out_name , "_pot" ) ;
% save( "-ascii" , out_name_potential , "out_potential" ) ;

toc
