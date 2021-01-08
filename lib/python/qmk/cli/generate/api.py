"""This script automates the generation of the QMK API data.
"""
from pathlib import Path
from shutil import copyfile
import json

from milc import cli

from qmk.datetime import current_datetime
from qmk.info import info_json
from qmk.keyboard import list_keyboards


@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't write the data to disk.")
@cli.subcommand('Creates a new keymap for the keyboard of your choosing', hidden=False if cli.config.user.developer else True)
def generate_api(cli):
    """Generates the QMK API data.
    """
    api_data_dir = Path('api_data')
    v1_dir = api_data_dir / 'v1'
    keyboard_list = v1_dir / 'keyboard_list.json'
    keyboard_all = v1_dir / 'keyboards.json'
    usb_file = v1_dir / 'usb.json'

    if not api_data_dir.exists():
        api_data_dir.mkdir()

    kb_all = {'last_updated': current_datetime(), 'keyboards': {}}
    usb_list = {'last_updated': current_datetime(), 'devices': {}}

    # Generate and write keyboard specific JSON files
    for keyboard_name in list_keyboards():
        kb_all['keyboards'][keyboard_name] = info_json(keyboard_name)
        keyboard_dir = v1_dir / 'keyboards' / keyboard_name
        keyboard_info = keyboard_dir / 'info.json'
        keyboard_readme = keyboard_dir / 'readme.md'
        keyboard_readme_src = Path('keyboards') / keyboard_name / 'readme.md'

        keyboard_dir.mkdir(parents=True, exist_ok=True)
        keyboard_json = json.dumps({'last_updated': current_datetime(), 'keyboards': {keyboard_name: kb_all['keyboards'][keyboard_name]}})
        if not cli.args.dry_run:
            keyboard_info.write_text(keyboard_json)
            cli.log.debug('Wrote file %s', keyboard_info)

            if keyboard_readme_src.exists():
                copyfile(keyboard_readme_src, keyboard_readme)
                cli.log.debug('Copied %s -> %s', keyboard_readme_src, keyboard_readme)

        if 'usb' in kb_all['keyboards'][keyboard_name]:
            usb = kb_all['keyboards'][keyboard_name]['usb']

            if usb['vid'] not in usb_list['devices']:
                usb_list['devices'][usb['vid']] = {}

            if usb['pid'] not in usb_list['devices'][usb['vid']]:
                usb_list['devices'][usb['vid']][usb['pid']] = {}

            usb_list['devices'][usb['vid']][usb['pid']][keyboard_name] = usb

    # Write the global JSON files
    # Note: This is 70mb of JSON as of Jan 2021, and will only get bigger. If the size becomes a problem we can switch to a more memory efficient process that doesn't let us dry run as easily.
    keyboard_list_json = json.dumps({'last_updated': current_datetime(), 'keyboards': sorted(kb_all['keyboards'])})
    keyboard_all_json = json.dumps({'last_updated': current_datetime(), 'keyboards': sorted(kb_all['keyboards'])})
    usb_json = json.dumps(usb_list)

    if not cli.args.dry_run:
        keyboard_list.write_text(keyboard_list_json)
        cli.log.debug('Wrote file %s', keyboard_list)
        keyboard_all.write_text(keyboard_all_json)
        cli.log.debug('Wrote file %s', keyboard_all)
        usb_file.write_text(usb_json)
        cli.log.debug('Wrote file %s', usb_file)
        cli.log.info('Wrote API data to %s', api_data_dir.resolve())
