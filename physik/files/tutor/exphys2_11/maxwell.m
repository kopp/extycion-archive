
is_script = 1 ; % kein finction file sondern script


% konst
R = 8.314472 % J / mol K
% Parameter von vorher [SI]
a = 0.367 % Pa m^2 / mol
b = 43e-6 % m^3
% Temp
T = 300 % K
global R a b T ;

function y = p(V)
	global R a b T ;
	y = R .* T ./ (V - b) - a ./ V.^2 ;
end


% interessanter V-Bereich
V = [ 2.2*b : 1e-7 : 5*b ] ;
% gib p(V) aus
p = p(V) ;
plot( V , p ) ;



% Waehle Start-Y-Wert fuer Maxwellkonstruktion
p_start = input( 'Start-Y-Wert fuer Maxwellkonstruktion angeben: ' );
% p_start = 6.9e6

% schrittweise Y-Wert anpassen, bis integral==0
epsilon = 1e-1 % so viel darf integral von 0 verschieden sein
delta = 1e3 % gehe pro Schritt so weit in Y Richtung
finder = 5e3 % so viel darf der finder in Y Richtung abweichen
% statt finder auch fzero verwenden...

% bestimme, wo p = p_start
% ROOT = @(V)R .* T ./ (V - b) - a ./ V.^2-p_start ;
% lower_bound = fzero( ROOT , V(1) )
% upper_bound = fzero( ROOT , V(floor(length(V)/4)) )
lower_bound = V( ( find( abs( p-p_start ) < finder ) )( 1 ) )
upper_bound = V( ( find( abs( p-p_start ) < finder ) )( end ) )
integral = quad( @(V)p_int(V)-p_start , lower_bound , upper_bound ) 

plot( V , p , V , p_start.*ones(size(V)) , lower_bound.*ones(size(V)) , p , upper_bound.*ones(size(V)), p )
input( 'weiter' ) ;


while true
	% ROOT = @(V)R .* T ./ (V - b) - a ./ V.^2-p_start ;
	% lower_bound_old = lower_bound ; upper_bound_old = upper_bound ;
	% lower_bound = fzero( ROOT , lower_bound_old ) ;
	% upper_bound = fzero( ROOT , upper_bound_old ) ;
	lower_bound = V( ( find( abs( p-p_start ) < finder ) )( 1 ) ) ;
	upper_bound = V( ( find( abs( p-p_start ) < finder ) )( end ) ) ;
	integral = quad( @(V)p_int(V)-p_start , lower_bound , upper_bound ) ;

	if( abs( integral ) < epsilon ) 
		break 
	end
	if( integral > epsilon ) 
		p_start += delta  ;
	end
	if( integral < -epsilon ) 
		p_start -= delta  ;
	end
	% plot( V , p , V , p_start.*ones(size(V)) , lower_bound.*ones(size(V)) , p , upper_bound.*ones(size(V)), p )
	% pause
end

% Maxwellkonstruktion muss zu p_start
p_final = p_start


% plot( V , p , V , p_start.*ones(size(V)) )
plot( V , p , V , p_start.*ones(size(V)) , lower_bound.*ones(size(V)) , p , upper_bound.*ones(size(V)), p )
