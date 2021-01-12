ORG 100H

MOV A, #(0xff & __const_label_0);
MOV A, #(0xff&(( 0xff00&__const_label_0) >>8));

__const_label_0:
;DB 0x3f 


; opand
; # expr
;
; expr
; --additive_expr
;---- multi_expr
;-----not_expr
;-----expr_elem
;-------( expr )


;; expr
; --additive_expr
;---- multi_expr
;-----not_expr
;-------expr_elem & expr_elem


; expr_elem
; -----( expr )

; expr
; --additive_expr
;---- multi_expr
;-----not_expr
; expr_elem SHIFT_RIGHT expr_elem


;expr_elem
;I_CONSTANT

;expr_elem
;-- ( expr )
;expr
; --additive_expr
;---- multi_expr
;-----not_expr
;expr_elem & expr_elem

;expr_elem
;TK_KEYWORD

;expr_elem
;I_CONSTANT



