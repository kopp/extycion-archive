% gesucht:
% integrationsgtenzen sodass gaussglockenintegral genau 0.9 ist

% definiere gauss glocke
function y = f(x)
y = exp( - x.^2 ./ 2 ) ./ sqrt( 2 .* pi ) ;
end
% anschauen
x = [ -10:0.1:10] ;
plot( x , f(x) ) ;
% normierung testen
quad( "f" , -inf , inf  ) 
% was wir eigentlich wollen: Integral der Gauss glocke von -b bis b
function y = p(n)
y = quad( "f" , -n , n ) ;
end
% test
p(1)
p(2)
% wir wollen irgendeinen wert zwischen 1 und 2; deshalb
range =  [1:0.01:2] ;
% hier sollen werte rein
erg = zeros( length( range ), 2 ) ;
% schleife : Jeweils integrieren
for ii = [1:length(range)]
erg(ii,:) = [range(ii) p(range(ii))] ;
end
% ergebnis anschauen
plot( erg(:,1), erg(:,2) )
% save( "-ascii" , "quadrature.oct" , "erg" ) ;

