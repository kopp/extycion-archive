% compute Kramer time for given potential
% (this relies on entering the formula for potential and its derivatives
% manually!)

% potentials are measured in units of kT


%% Parameter %%

a_range = [ 0 : 0.2 : 7.6 ] ' ;
%^ for values of a larger than 7.6 the roots become imaginary...



%% Variables %%

% kramers time for left (:,1) and right (:,2) well
% in units of 6 pi \eta r / kT
t_kramer = zeros( length( a_range ) , 2 ) ;
% energy barriers (like t_kramer)
% in units of kT
barrier = zeros( length( a_range ) , 2 ) ;



%% Functions %%

% -- function u = V(x)
    % return default potential
function u = V(x)
    u = 5 .* (x-1).^2 .* (x+1).^2 ;
end

% -- function u = W(x)
    % return modified potential
function u = W(x,a)
    u = V(x)+a*x ;
    % u = polyval( [ 5 0 -10 a 5 ] , x ) ;
end

% -- function poly = abl(a)
    % return polynom coefficient vector for V' with specified a
function poly = abl(a)
    poly = [ 20 0 -20 a ] ;
end

% polynom coefficients for the second derivative
poly_abl2 = [ 60 0 -20 ] ;




%% Program %%

tic

% loop over different a and find roots
for ii = [ 1 : length( a_range ) ]
    % status output
    % [ ones(3,1)*a_range(ii) r V(r) W(r,a_range(ii)) ]
    % find roots and sort them
    r = sort( roots( abl( a_range(ii) ) ) ) ;
    % compute energy barrier
    a = a_range( ii ) ;
    barrier(ii,:) = [ W(r(2),a)-W(r(1),a)  ,  W(r(2),a)-W(r(3),a) ] ;
    % compute curvatures
    curv = polyval( poly_abl2 , r ) ;
    % and products of outer with central curvature
    curv_prod = [ curv(1)*curv(2) , curv(2)*curv(3) ] ;
    % compute kramer time
    t_kramer(ii,:) = 2*pi ./ sqrt( abs( curv_prod ) ) .* exp( barrier(ii,:) ) ;
end

toc


%% Output %%

% plot t_kramer
semilogy( a_range , t_kramer(:,1) , ";left;"  , a_range , t_kramer(:,2) , ";right;" ) ;
xlabel( "additive linear potential  " ) ;
ylabel( "Kramers time" );
print( "kramers_t.eps" , "-deps" , "-color" ) ;

pause

% plot potential barriers
plot( a_range , barrier(:,1) , ";left;"  , a_range , barrier(:,2) , ";right;" ) ;
xlabel( "additive linear potential  " ) ;
ylabel( "Potential Differences" );
print( "kramers_DE.eps" , "-deps" , "-color" ) ;
