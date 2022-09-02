function finallast = SA(tend)
    tend = 10000 ;
    temperature = 1000 ;
    min_temperature = 0.001 ;
    delta_target = 150 ;
    alpha = 0.9 ;
    last_now = 0.05 ;
    last_best = last_now ;
    [ttt, tmp] = getsimulate(last_now, tend) ;
    delta_now =  abs(pend_Pca(ttt, tmp) - delta_target) ;
    delta_best = delta_now ;
    while temperature > min_temperature
        last_tmp = last_now + 0.1 * (rand() * 2 - 1) ;
        if(last_tmp > 0 && last_tmp < 1) 
   
            [ttt, tmp] = getsimulate(last_now, tend) ;
            delta_tmp = abs(pend_Pca(ttt, tmp) - delta_target) ;

            if(delta_tmp < delta_now)
               delta_now = delta_tmp;
               last_now = delta_tmp;
               if(delta_tmp < delta_best)
                  delta_best = delta_tmp ;
                  last_best = last_tmp ;
               end
            elseif rand() < exp(- (delta_now - delta_best)/temperature)
                delta_now = delta_tmp ;
                last_now = last_tmp ;
            end
        
            temperature = temperature * alpha ;
        end
    end

end
