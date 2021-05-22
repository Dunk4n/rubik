/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rubik.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 16:01:28 by niduches          #+#    #+#             */
/*   Updated: 2021/05/23 00:37:25 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUBIK_HPP
# define RUBIK_HPP

# include <iostream>
# include "graphique.hpp"

class Rubik
{
	public:
	enum	e_instructions
	{
		FRONT,
		RIGHT,
		UP,
		BACK,
		LEFT,
		DOWN,
		NB_INSTRUCTIONS
	};
	enum	e_color
	{
		BLUE,
		RED,
		YELLOW,
		GREEN,
		ORANGE,
		WHITE,
		NB_COLOR
	};
	struct	s_mat4;

	struct	s_vec2f
	{
		float	x;
		float	y;

		s_vec2f(float x = 0, float y = 0)
		{
			this->x = x;
			this->y = y;
		}
	};
	struct	s_vec3f
	{
		float	x;
		float	y;
		float	z;

		s_vec3f(float x = 0, float y = 0, float z = 0)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		bool	operator==(const s_vec3f &right) const
		{
			return (this->x == right.x && this->y == right.y && this->z == right.z);
		}
		bool	operator!=(const s_vec3f &right) const
		{
			return (!(*this == right));
		}

		s_vec3f	operator+(const s_vec3f &right)
		{
			s_vec3f	vec;

			vec.x = this->x + right.x;
			vec.y = this->y + right.y;
			vec.z = this->z + right.z;
			return (vec);
		}
		s_vec3f	operator-(const s_vec3f &right)
		{
			s_vec3f	vec;

			vec.x = this->x - right.x;
			vec.y = this->y - right.y;
			vec.z = this->z - right.z;
			return (vec);
		}
		s_vec3f	operator*(const s_mat4 &right)
		{
			s_vec3f	vec;

			vec.x = right.value[0][0] * this->x + right.value[0][1] * this->y +
			right.value[0][2] * this->z + right.value[0][3];
			vec.y = right.value[1][0] * this->x + right.value[1][1] * this->y +
			right.value[1][2] * this->z + right.value[1][3];
			vec.z = right.value[2][0] * this->x + right.value[2][1] * this->y +
			right.value[2][2] * this->z + right.value[2][3];
			return (vec);
		}
		s_vec3f	operator*(float nb)
		{
			return ((s_vec3f){this->x * nb, this->y * nb, this->z * nb});
		}
		s_vec3f	&operator*=(const s_mat4 &right)
		{
			*this = *this * right;
			return (*this);
		}
		s_vec3f	&operator*=(float nb)
		{
			this->x *= nb;
			this->y *= nb;
			this->z *= nb;
			return (*this);
		}
	};

	struct	s_mat4
	{
		float	value[4][4];

		s_mat4(void)
		{
			for (uint i = 0; i < 16; ++i)
				((float*)(this->value))[i] = 0;
		}
		bool	operator==(const s_mat4 &right) const
		{
			for (uint i = 0; i < 16; ++i)
			{
				if (((float*)(this->value))[i] != ((float*)(right.value))[i])
					return (false);
			}
			return (true);
		}
		bool	operator!=(const s_mat4 &right) const
		{
			return (!(*this == right));
		}

		s_mat4	operator*(const s_mat4 &right)
		{
			s_mat4	mat;
	
			for (uint i = 0; i < 4; ++i)
			{
				for (uint j = 0; j < 4; ++j)
				{
					mat.value[i][j] = 0;
					for (uint k = 0; k < 4; ++k)
						mat.value[i][j] += this->value[k][j] * right.value[i][k];
				}
			}
			return (mat);
		}
		s_mat4	&operator*=(const s_mat4 &right)
		{
			s_mat4	mat;

			for (uint i = 0; i < 4; ++i)
			{
				for (uint j = 0; j < 4; ++j)
				{
					mat.value[i][j] = 0;
					for (uint k = 0; k < 4; ++k)
						mat.value[i][j] += this->value[k][j] * right.value[i][k];
				}
			}
			*this = mat;
			return (*this);
		}
	};

	typedef s_vec2f		vec2;
	typedef s_vec3f		vec3;
	typedef s_mat4		mat4;

	struct	s_cube
	{
		vec3	pos;
		mat4	rot;
		char	id;
		char	dir;
	};

	typedef s_cube			Cube;


	Rubik(void);
	Rubik(char *instructions);
	virtual ~Rubik(void);

	void	rotate_front(char factor);
	void	rotate_right(char factor);
	void	rotate_up(char factor);
	void	rotate_back(char factor);
	void	rotate_left(char factor);
	void	rotate_down(char factor);

	void	set_display(bool v) { this->disp = v; }
	bool	get_display(void) { return (this->disp); }
	void	chage_resolve(int nb) { this->chose_sol = nb; }
	int		get_resolve(void) { return (this->chose_sol); }

	void	display_color(void);
	void	display_solution(void);
	void	set_generateur(int nb);
	bool	get_graphique(void) { return (this->graphique); }
	void	set_graphique(bool v) { this->graphique = v; }

	bool	get_human_readable(void) { return (this->human_readable); }
	void	set_human_readable(bool v) { this->human_readable = v; }

	void	resolve(void);
	void	format(void);

	private:

	void	make_instruction(char *&instructions, int face);
	bool	is_another_instruction(char *instructions) const;
	void	make_instructions(char *instructions, int face = 0);
	void	make_instructions(const char *instructions, int face = 0);
	void	make_instructions(std::string instructions, int face = 0);
	bool	is_space(char c) const;
	void	pass_spaces(char *&instructions) const;
	int		get_instruction(char *&instructions, int face) const;
	char	get_factor(char *&instructions) const;
	int		strncmp(const char *s1, const char *s2, size_t n) const;
	int		strlen(const char *str) const;
	mat4	identity_matrix(void) const;
	void	init_cubes(void);
	void	set_color(char *colors, Cube cube);
	int		get_color(Cube cube, int face);
	int		get_face(Cube cube, int face);
	int		get_pos_in_face(Cube cube, int face);
	void	display_square(char *color, int nb, int offset);
	void	display_multiple_square(char *color, int *tab, int size, int offset);
	void	round_vec3(Rubik::vec3 &vec);
	Rubik::vec3	normalize_vector(Rubik::vec3 vec) const;
	Rubik::mat4	rotation_matrix(float angl, Rubik::vec3 vec) const;
	void	rotation_matrix_result(Rubik::mat4 &res, Rubik::mat4 tmp, Rubik::mat4 mat, int nb);
	void	display_instruction(int instr, int factor);

	void	init_color(void);

	void	put_edges(void);
	void	put_edge(uint face);
	void	put_edge_down(uint face);
	void	put_edge_in_face(uint face);

	void	put_corners(void);
	void	put_corner(uint face);
	void	put_corner_down(uint face);
	void	put_corner_in_face(uint face);

	void	put_belges(void);
	void	put_belge(uint face);
	void	put_belge_down(uint face, uint idx);
	bool	put_belge_in_face(uint face, uint idx);

	void	cross(void);
	void	good_cross(void);
	void	put_cross_in_face(void);

	void	put_down_corner(void);
	bool	all_down_corner_in_place(void);
	bool	down_corner_in_place(uint face);

	void	put_right_down_corner(void);
	bool	down_corner_in_right_place(uint idx);
	bool	all_down_corner_in_right_place(void);

	void	set_id(vec3 pos, int *id, int *dir);
	void	make_window(void);

	void	make_new_instruction(char *&instr, s_anim *anim, Transform *tab, int nb_cube);
	int		get_instruction_graphique(char *&instructions) const;
	void	set_rubik(Transform *tab, int nb_cube);

	static const char	*instructions_name[NB_INSTRUCTIONS];
	static const int	face[NB_COLOR][3];
	static const char	*colors_code[NB_COLOR + 1];
	static const int	face_coords[NB_COLOR][6];
	static const int	face_rotate[NB_COLOR][3];
	static const int	color_rotate[4][4][4];

	std::string	solution;
	std::string	instruction;
	int			size;
	float		center;
	uint		nb_cube;
	Cube		*cubes;
	char		*colors;
	bool		disp;
	bool		sol;
	bool		graphique;
	bool		human_readable;
	char		chose_sol;
};

#endif /* RUBIK_HPP */
