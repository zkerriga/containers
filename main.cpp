/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:52:02 by zkerriga          #+#    #+#             */
/*   Updated: 2020/11/26 10:52:04 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>

int main() {
	std::list<std::string >	s1;

	std::list<std::string >::const_iterator ite = s1.end();
	std::cout << *ite << std::endl;
	return 0;
}
