flight(edirne,edremit,5).
flight(edremit,edirne,5).

flight(erzincan,edremit,7).
flight(edremit,erzincan,7).		

flight(istanbul,izmir,3).
flight(izmir,istanbul,3).

flight(izmir,antalya,1).
flight(antalya,izmir,1).

flight(antalya,diyarbakir,5).
flight(diyarbakir,antalya,5).

flight(diyarbakir,konya,1).
flight(konya,diyarbakir,1).

flight(konya ,ankara,8).
flight(ankara,konya,8).

flight(ankara,istanbul,5).
flight(istanbul,ankara,5).

flight(ankara,izmir,6).
flight(izmir,ankara,6).

flight(trabzon ,ankara,2).
flight(ankara,trabzon , 2).

flight(trabzon,istanbul,3).
flight(istanbul,trabzon,3).

flight(konya ,kars,5).
flight(kars , konya,5).

flight(gaziantep,kars,3).
flight(kars,gaziantep,3).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Q1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%

route(X,Y,C) :- flight(X,Y,C).    %if any flight is occur between X , Y.
route(X , Y , C) :- findcost(X , Y , C , []). %I used a list that holds the verteces
findcost(X , Y , C , _) :- flight(X , Y , C).
findcost(X , Y , C , L) :- \+ member(X , L),flight(X , Z , A), 					%Control the X city is in L and call flight
							findcost(Z , Y , B , [X|L]),X\=Y,C is A + B.		%then call the recursive part with [X]+L and calculate cost.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Q2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%

:-dynamic(mincost/1).							%dynamic variable
croute(X , Y , C) :- findmincost(X , Y , C).	%base condition


% '!' is used for stoping the recursion after find a result in tfis part.
findmincost(X , Y , C) :- \+ mincost(_),route(X , Y , C1),	%recursion part for C1
						  assertz(mincost(C1)),!,findmincost(X,Y,C). 							                              

%fail is used fr trying another branch in the recursion.
findmincost(X, Y, _) :- route(X, Y, C1), mincost(C2), C1 < C2,	%recursion part for C2
                        retract(mincost(C2)),asserta(mincost(C1)),fail.
                                               
findmincost(_, _, C) :- mincost(C), retract(mincost(C)).				% last part for minumum cost

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Q3 %%%%%%%%%%%%%%%%%%%%%%%%%%%%

%sension(N , T , R).

sension(a , 10 , 101).
sension(b , 12 , 104).
sension(c , 11 , 102).
sension(d , 16 , 103).
sension(e , 17 , 103).

%added sensions   %%%%%%  Q3.0  %%%%%%

sension(f , 14 , 104).
sension(g , 13 , 101).
sension(h , 16 , 102).
sension(k , 14 , 101).

%enrollment(S , A).

enrollment(a , 1).
enrollment(b , 1).
enrollment(a , 2).
enrollment(b , 3).
enrollment(c , 4).
enrollment(d , 5).
enrollment(d , 6).
enrollment(a , 6).

%added enrolments  %%%%%%  Q3.0  %%%%%%

enrollment(f , 7).
enrollment(h , 7).
enrollment(g , 8).
enrollment(c , 9).
enrollment(e , 8).
enrollment(g , 9).
enrollment(k , 10).
enrollment(k , 3).
enrollment(k , 11).


whose(X , Y) :- enrollment(Y , X). %whose(X,Y) – X is enrolled in session Y
when(X ,Y) :- sension(X , Y ,_).   %when(X,Y) – time of the session X is Y
where(X , Y) :- sension(X , _ , Y). %where(X,Y) – place of the session X is Y

%%%%%%  Q3.1  %%%%%%

schedule(S,P,T) :- enrollment(X , S) , sension(X , P ,T). %gives the time and place according to the ID.


%%%%%%  Q3.2  %%%%%%
usage(P , T) :- where(X , P), when(X , T).	%that gives the usage times of a room.

%%%%%%  Q3.3  %%%%%%

findtimes(X , Y , T1 , T2) :- when(X , T1) , when(Y ,T2).
findplaces(X , Y , P1 ,P2) :- where(X , P1), where(Y , P2).



conflict(X,Y) :- findtimes(X ,Y , T1 , T2) ,findplaces(X , Y , P1 , P2) ,  %that gives true if sessions X and Y conflict due to room or time. 
				(T1==T2 ; P1 == P2) , !.


%%%%%%  Q3.4  %%%%%%

%that gives true if attandees X and Y are present in the same room at the same time.
meet(X,Y) :- enrollment(S1 , X) , enrollment(S2,Y), S1==S2,!.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Q4 %%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Q4.1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%

union([] , [] , []).  	%three lists are empty so result is empty
union([] ,S , S).		%if first list empty then second one is the result.
union(L , [] , L).		%if second one is empty than first one is the result	

%if head of the firts list is not in second one then add the heads recursively into the
%list until the first one is empty.

union([H|T] , S , [H|U]) :- \+member(H , S) ,union(T , S , U) . 

%if head of the firts list is in second one then without adding the head call the union with tail.

union([H|T] , S , U) :- member(H , S) ,union(T , S , U) .

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Q4.2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%

intersect([],[],[]).  %three lists are empty so result is empty
intersect([],_,[]).	  %if first list empty then the result is empty.
intersect(_,[],[]).	  %if second list empty then the result is empty.


%if head of the firt list is  in second one then add the heads recursively into the
%list until the first one is empty.

intersect([H|T],L2,[H|I]) :- member(H , L2), intersect(T,L2,I),!.

%if head of the firt list is not in second one then without adding the head call 
%the intersect with tail.

intersect([H|T],L2,I) :- \+member(H , L2), intersect(T,L2,I).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Q4.3 %%%%%%%%%%%%%%%%%%%%%%%%%%%%

%append part to use flatten. Take two lists to append the elements into third list
insert([] , L2 , L2).
insert(L1 , [] , L1).
insert(L1 , [H|T] , [H|R]):- insert(L1 , T , R).

flatten([] , []) :- !. 					%when first list empty then make the result empty and cut.

%firstly find F1 that is first flatten part came from first recursive with H(Head of the given list),
%then second part is working and second recursive call is working with T(tail of the given list) and F2 is found.
%after that , these found flatten parts  are appended into the result then finish.

flatten([H|T],F) :- flatten(H , F1),flatten(T,F2),insert(F1, F2 , F ),!. 


flatten(L , [L]). %to make clear the result
