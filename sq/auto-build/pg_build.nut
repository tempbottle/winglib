
dofile( _self.path( "config.nut" ) );
local _cfg = CConfig();

function pg_run( mRequest, mHeaders, mGet, mPost ) : ( _cfg )
{
	// Ensure build scripts directory
	if ( !CSqFile().exists( _cfg.build_scripts_dir ) )
		CSqFile().mkdir( _cfg.build_scripts_dir );

	// Adding a build?
	if ( mPost[ "name" ] && mPost[ "desc" ] )
	{	local id = _self.unique();
		local cfg = CSqMulti();
		cfg[ "name" ].set( _self.trimws( mPost[ "name" ] ) );
		cfg[ "desc" ].set( _self.trimws( mPost[ "desc" ] ) );
		CSqFile().put_contents( _self.build_path( _cfg.build_scripts_dir, id ), cfg.serialize() );
	} // end if

	// Delete build?
	else if ( mGet[ "del" ] )
	{	local file = _self.build_path( _cfg.build_scripts_dir, mGet[ "del" ] );
		if ( CSqFile().exists( file ) )
			CSqFile().delete_file( file );
	} // end if

	// Execute now?
	else if ( mGet[ "edit" ] )
		return edit_builds( mRequest, mHeaders, mGet, mPost );

	return show_builds( mRequest, mHeaders, mGet, mPost );
}

function show_builds( mRequest, mHeaders, mGet, mPost ) : ( _cfg )
{
	local content = @"
		<table width='95%'>
			<tr>
				<td></td>
				<td>
					<nobr><b>Name</b></nobr>
				</td>
				<td>&nbsp;&nbsp;&nbsp;</td>
				<td>
					<nobr><b>Description</b></nobr>
				</td>
				<td>
				</td>
			</tr>
		";

	content += @"
			<form action='/build' method='post'>
				<tr>
					<td></td>
					<td>
						<input name='name' id='name' type='text' style='width:150'>
					</td>
					<td></td>
					<td width='100%'>
						<input name='desc' id='desc' type='text' style='width:100%'>
					</td>
					<td>
						<input type='submit' value='Add'>
					</td>
				</tr>
				<tr>
					<td colspan='99'>
						<hr>
					</td>
				</tr>
		";

	local scripts = CSqFile().get_dirlist( _cfg.build_scripts_dir, "*", 1, 0 );
	local records = "";
	foreach( k,v in scripts )
	{
		local cfg = CSqMulti();
		cfg.deserialize( CSqFile().get_contents( _self.build_path( _cfg.build_scripts_dir, k ) ) );

		local dlink = ( mGet[ "rdel" ] && mGet[ "rdel" ] == k )
					  ? "[<a title='Delete' href='/build?del=" + k + "'><b>SURE?</b></a>]"
					  : "[<a title='Delete' href='/build?rdel=" + k + "'><b>x</b></a>]";

		records = @"
			<tr>
				<td>
					<table>
						<tr>
							<td>
								" + dlink + @"
							</td>
							<td>
								[<b><a href='/build?edit=" + k + @"'>Edit</a></b>]
							</td>
						</tr>
					</table>
				</td>
				<td style='border-bottom:solid 1px #808080'>
					" + cfg.get( "name" ).str() + @"
				</td>
				<td></td>
				<td style='border-bottom:solid 1px #808080'>
					" + cfg.get( "desc" ).str() + @"
				</td>
			</tr>
			" + records;

	} // end foreach

	content += records;
	content += @"
				</table>
			</form>
		";

	return content;
}

function show_step( inf )
{
	if ( !inf[ "type" ] )
		return "n";

	switch( inf[ "type" ].str() )
	{
		case "co" :
			return inf[ "repo" ].str() + " checkout " + inf[ "link" ].str() + " " + inf[ "to" ].str();

		case "dl" :
			return "Download : " + inf[ "link" ].str();

		case "cmd" :
			return "Execute : " + inf[ "cmd" ].str();

		case "goto" :
			return "Goto Step : " + _self.tolong( inf[ "goto" ].str() );

		case "cd" :
			return "Change Directory : " + inf[ "dir" ].str();

		case "md" :
			return "Make Directory : " + inf[ "dir" ].str();

	} // end switch

	return "Unknown step type : " + inf[ "type" ].str();
}

function show_add_step( cfg, mRequest, mHeaders, mGet, mPost ) : ( _cfg )
{
	local next = _self.tolong( mPost.get( "step" ) );
	if ( !next )
	{	next = _self.tolong( cfg[ "next" ].str() );
		if ( !next ) next = 10;
	} // end if

	local options = @"<select name='type' id='type' onchange='OnSelectStepType(this)'>
				<option value='' selected></option>
				<option value='cmd'>Execute Command</option>
				<option value='co'>Checkout</option>
				<option value='dl'>Download</option>
				<option value='cd'>Change Directory</option>
				<option value='md'>Make Directory</option>
				<option value='goto'>Goto</option>
			</select>
		";

	local content = @"
			<script language='javascript'>

				var cur_sel = '';
				function OnSelectStepType( obj )
				{
					if ( cur_sel.length )
						document.getElementsByName( cur_sel )[ 0 ].style.display = 'none';

					if ( obj.value.length )
						document.getElementsByName( obj.value )[ 0 ].style.display = '';

					cur_sel = obj.value;
				}

			</script>

			<form action='/build?edit=" + mGet[ "edit" ] + @"&add_step=1' method='post'>
				<table
					width='100%'
					style='border-left:solid 1px;border-top:solid 1px;border-right:solid 1px;border-bottom:solid 1px'
				>
					<tr>
						<td colspan='99' style='border-bottom:solid 1px " + _cfg.col_dkline + @"'>
							<table>
								<tr>
									<td>
										<b>Add Step : </b>
									</td>
									<td>
										<input type='text' id='next' name='next' value=" + next + @" style='width:60;'>
									</td>
									<td>
										" + options + @"
									</td>
									<td align='right'>
										&nbsp;&nbsp;&nbsp;
										<input type='submit' value='Add'>
									</td>
								</tr>
							</table>
						</td>
					</tr>
					<tr>
						<td colspan='99'>
							<div id='cmd' name='cmd' style='display:none'>
								<table width='100%'>
									<tr>
										<td>
											Command
										</td>
										<td width='100%'>
											<input type='text' id='cmd' name='cmd' value='' style='width:100%'>
										</td>
									</tr>
								</table>
							</div>
							<div id='co' name='co' style='display:none'>
								<table width='100%'>
									<tr>
										<td>
											<select id='co_repo' name='co_repo'>
												<option value='svn'>SVN</option>
												<option value='cvs'>CVS</option>
												<option value='git'>GIT</option>
											</select>
										</td>
										<td>
											Link
										</td>
										<td width='100%'>
											<input type='text' id='co_link' name='co_link' value='' style='width:100%'>
										</td>
										<td>
											Directory
										</td>
										<td>
											<input type='text' id='co_to' name='co_to' value='' style='width:200'>
										</td>
									</tr>
								</table>
							</div>
							<div id='dl' name='dl' style='display:none'>
								<table width='100%'>
									<tr>
										<td>
											Download
										</td>
										<td width='100%'>
											<input type='text' id='dl_link' name='dl_link' value='' style='width:100%'>
										</td>
									</tr>
								</table>
							</div>
							<div id='goto' name='goto' style='display:none'>
								<table width='100%'>
									<tr>
										<td>
											Goto&nbsp;Step
										</td>
										<td width='100%'>
											<input type='text' id='goto' name='goto' value='' style='width:150'>
										</td>
									</tr>
								</table>
							</div>
							<div id='cd' name='cd' style='display:none'>
								<table width='100%'>
									<tr>
										<td>
											Directory
										</td>
										<td width='100%'>
											<input type='text' id='cd_dir' name='cd_dir' value='' style='width:100%'>
										</td>
									</tr>
								</table>
							</div>
							<div id='md' name='md' style='display:none'>
								<table width='100%'>
									<tr>
										<td>
											Directory
										</td>
										<td width='100%'>
											<input type='text' id='md_dir' name='md_dir' value='' style='width:100%'>
										</td>
									</tr>
								</table>
							</div>
						</td>
					</tr>
				</table>
		";

	content += @"
				</table>
			</form>
		";

	return content;
}

function edit_builds( mRequest, mHeaders, mGet, mPost ) : ( _cfg )
{
	local cfg = CSqMulti();
	cfg.deserialize( CSqFile().get_contents( _self.build_path( _cfg.build_scripts_dir, mGet[ "edit" ] ) ) );

	if ( !cfg.size() )
		return "Invalid Build";

	// Are we adding a step?
	if ( mGet[ "add_step" ] && mPost[ "type" ] && mPost[ "type" ].len() )
	{
		local next = _self.tolong( mPost.get( "next" ) );
		if ( !next )
		{	next = _self.tolong( cfg[ "next" ].str() );
			if ( !next ) next = 10;
		} // end if
		local id = format( "%.6d", next );

		cfg[ "s" ][ id ][ "type" ].set( mPost[ "type" ] );
		switch( mPost[ "type" ] )
		{
			case "co" :
				cfg[ "s" ][ id ][ "repo" ].set( mPost[ "co_repo" ] );
				cfg[ "s" ][ id ][ "link" ].set( mPost[ "co_link" ] );
				cfg[ "s" ][ id ][ "to" ].set( mPost[ "co_to" ] );
				break;

			case "dl" :
				cfg[ "s" ][ id ][ "link" ].set( mPost[ "dl_link" ] );
				break;

			case "cd" :
				cfg[ "s" ][ id ][ "dir" ].set( mPost[ "cd_dir" ] );
				break;

			case "md" :
				cfg[ "s" ][ id ][ "dir" ].set( mPost[ "md_dir" ] );
				break;

			case "goto" :
				cfg[ "s" ][ id ][ "goto" ].set( mPost[ "goto" ] );
				break;

			case "cmd" :
				cfg[ "s" ][ id ][ "cmd" ].set( mPost[ "cmd" ] );
				break;

		} // end switch

		cfg[ "next" ].set( format( "%.6d", ( next + 10 ) ) );
		CSqFile().put_contents( _self.build_path( _cfg.build_scripts_dir, mGet[ "edit" ] ), cfg.serialize() );

	} // end if

	// Remove step
	else if ( mGet[ "del_step" ] )
	{
		local id = format( "%.6d", _self.tolong( mGet[ "del_step" ] ) );
		cfg[ "s" ].unset( id );
		CSqFile().put_contents( _self.build_path( _cfg.build_scripts_dir, mGet[ "edit" ] ), cfg.serialize() );

	} // end if

	// Renumber steps?
	else if ( mGet[ "renum" ] && cfg[ "s" ].size() )
	{
		local num = 0;
		local cp = CSqMulti();
		foreach ( k,v in cfg[ "s" ] )
			cp.get( format( "%.6d", ( num += 10 ) ) ).copy( cfg[ "s" ][ k ] );

		cfg.unset( "s" );
		cfg[ "s" ].copy( cp );

		cfg[ "next" ].set( format( "%.6d", ( num + 10 ) ) );
		CSqFile().put_contents( _self.build_path( _cfg.build_scripts_dir, mGet[ "edit" ] ), cfg.serialize() );

	} // end if

	else if ( mGet[ "build_now" ] )
	{
		_self.execute1( 0, "/build_mgr", "Build", mGet[ "edit" ] );

	} // end else if

	local content = @"
		<table width='100%' bgcolor='" + _cfg.col_shade + @"'>
			<tr>
				<td></td>
				<td>
					<nobr><b>" + cfg[ "name" ].str() + @"</b></nobr>
				</td>
				<td>&nbsp;&nbsp;&nbsp;-&nbsp;&nbsp;&nbsp;</td>
				<td>
					<nobr><b>" + cfg[ "desc" ].str() + @"</b></nobr>
				</td>
				<td width='100%' align='right'>
					[<a title='Renumber' href='/build?edit=" + mGet[ "edit" ] + @"&build_now=1'><b>BUILD</b></a>]
				</td>
			</tr>
			</table>
			<hr>
			<table width='95%'>
		";

	content += @"
			</table>
		" + show_add_step( cfg, mRequest, mHeaders, mGet, mPost );

	content += @"
			<table width='100%' cellspacing='0'>
				<tr>
					<td style='border-bottom:solid 1px'>
						[<a title='Renumber' href='/build?edit=" + mGet[ "edit" ] + @"&renum=1'><b>*</b></a>]
					</td>
					<td style='border-bottom:solid 1px'>
						&nbsp;
					</td>
					<td width='100%' style='border-bottom:solid 1px'>
						&nbsp;
					</td>
				</tr>
		";

	local row = 0;
	foreach ( k,v in cfg[ "s" ] )
	{
		local n = _self.tolong( k );
		local rowcolor = ( row++ & 1 ) ? " bgcolor='" + _cfg.col_shade + "'" : "";

		content += @"
				<tr" + rowcolor + @">
					<td>
						[<a title='Delete' href='/build?edit=" + mGet[ "edit" ] + @"&del_step=" + n + @"'><b>x</b></a>]
					</td>
					<td style='border-right:solid 1px " + _cfg.col_dkline + @"'>
						" + n + @"&nbsp;
					</td>
					<td>
						&nbsp;" + show_step( v ) + @"
					</td>
				</tr>
			";

	} // end foreach

	content += @"
			</table>
		";

	return content;
}
